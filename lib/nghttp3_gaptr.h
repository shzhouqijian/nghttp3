/*
 * nghttp3
 *
 * Copyright (c) 2019 nghttp3 contributors
 * Copyright (c) 2017 ngtcp2 contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NGHTTP3_GAPTR_H
#define NGHTTP3_GAPTR_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp3/nghttp3.h>

#include "nghttp3_mem.h"
#include "nghttp3_range.h"
#include "nghttp3_psl.h"

/*
 * nghttp3_gaptr maintains the gap in the range [0, UINT64_MAX).
 */
typedef struct {
  /* gap maintains the range of offset which is not received
     yet. Initially, its range is [0, UINT64_MAX). */
  nghttp3_psl gap;
  /* mem is custom memory allocator */
  const nghttp3_mem *mem;
} nghttp3_gaptr;

/*
 * nghttp3_gaptr_init initializes |gaptr|.
 *
 * This function returns 0 if it succeeds, or one of the following
 * negative error codes:
 *
 * NGHTTP3_ERR_NOMEM
 *     Out of memory.
 */
int nghttp3_gaptr_init(nghttp3_gaptr *gaptr, const nghttp3_mem *mem);

/*
 * nghttp3_gaptr_free frees resources allocated for |gaptr|.
 */
void nghttp3_gaptr_free(nghttp3_gaptr *gaptr);

/*
 * nghttp3_gaptr_push adds new data of length |datalen| at the stream
 * offset |offset|.
 *
 * This function returns 0 if it succeeds, or one of the following
 * negative error codes:
 *
 * NGHTTP3_ERR_NOMEM
 *     Out of memory
 */
int nghttp3_gaptr_push(nghttp3_gaptr *gaptr, uint64_t offset, size_t datalen);

/*
 * nghttp3_gaptr_first_gap_offset returns the offset to the first gap.
 * If there is no gap, it returns UINT64_MAX.
 */
uint64_t nghttp3_gaptr_first_gap_offset(nghttp3_gaptr *gaptr);

/*
 * nghttp3_gaptr_is_pushed returns nonzero if range [offset, offset +
 * datalen) is completely pushed into this object.
 */
int nghttp3_gaptr_is_pushed(nghttp3_gaptr *gaptr, uint64_t offset,
                            size_t datalen);

#endif /* NGHTTP3_GAPTR_H */
