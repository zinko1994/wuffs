#ifndef WUFFS_ZLIB_H
#define WUFFS_ZLIB_H

// Code generated by wuffs-c. DO NOT EDIT.

#ifndef WUFFS_BASE_HEADER_H
#define WUFFS_BASE_HEADER_H

// Copyright 2017 The Wuffs Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Wuffs requires a word size of at least 32 bits because it assumes that
// converting a u32 to usize will never overflow. For example, the size of a
// decoded image is often represented, explicitly or implicitly in an image
// file, as a u32, and it is convenient to compare that to a buffer size.
//
// Similarly, the word size is at most 64 bits because it assumes that
// converting a usize to u64 will never overflow.
#if __WORDSIZE < 32
#error "Wuffs requires a word size of at least 32 bits"
#elif __WORDSIZE > 64
#error "Wuffs requires a word size of at most 64 bits"
#endif

// WUFFS_VERSION is the major.minor version number as a uint32. The major
// number is the high 16 bits. The minor number is the low 16 bits.
//
// The intention is to bump the version number at least on every API / ABI
// backwards incompatible change.
//
// For now, the API and ABI are simply unstable and can change at any time.
//
// TODO: don't hard code this in base-header.h.
#define WUFFS_VERSION (0x00001)

// wuffs_base__slice_u8 is a 1-dimensional buffer (a pointer and length).
//
// A value with all fields NULL or zero is a valid, empty slice.
typedef struct {
  uint8_t* ptr;
  size_t len;
} wuffs_base__slice_u8;

// wuffs_base__buf1 is a 1-dimensional buffer (a pointer and length), plus
// additional indexes into that buffer, plus an opened / closed flag.
//
// A value with all fields NULL or zero is a valid, empty buffer.
typedef struct {
  uint8_t* ptr;  // Pointer.
  size_t len;    // Length.
  size_t wi;     // Write index. Invariant: wi <= len.
  size_t ri;     // Read  index. Invariant: ri <= wi.
  bool closed;   // No further writes are expected.
} wuffs_base__buf1;

// wuffs_base__limit1 provides a limited view of a 1-dimensional byte stream:
// its first N bytes. That N can be greater than a buffer's current read or
// write capacity. N decreases naturally over time as bytes are read from or
// written to the stream.
//
// A value with all fields NULL or zero is a valid, unlimited view.
typedef struct wuffs_base__limit1 {
  uint64_t* ptr_to_len;             // Pointer to N.
  struct wuffs_base__limit1* next;  // Linked list of limits.
} wuffs_base__limit1;

typedef struct {
  // TODO: move buf into private_impl? As it is, it looks like users can modify
  // the buf field to point to a different buffer, which can turn the limit and
  // mark fields into dangling pointers.
  wuffs_base__buf1* buf;
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so.
  struct {
    wuffs_base__limit1 limit;
    uint8_t* mark;
  } private_impl;
} wuffs_base__reader1;

typedef struct {
  // TODO: move buf into private_impl? As it is, it looks like users can modify
  // the buf field to point to a different buffer, which can turn the limit and
  // mark fields into dangling pointers.
  wuffs_base__buf1* buf;
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so.
  struct {
    wuffs_base__limit1 limit;
    uint8_t* mark;
  } private_impl;
} wuffs_base__writer1;

#endif  // WUFFS_BASE_HEADER_H

// ---------------- Use Declarations

// ---------------- BEGIN USE "std/flate"

#ifndef WUFFS_FLATE_H
#define WUFFS_FLATE_H

// Code generated by wuffs-c. DO NOT EDIT.

// ---------------- Use Declarations

#ifdef __cplusplus
extern "C" {
#endif

// ---------------- Status Codes

// Status codes are int32_t values:
//  - the sign bit indicates a non-recoverable status code: an error
//  - bits 10-30 hold the packageid: a namespace
//  - bits 8-9 are reserved
//  - bits 0-7 are a package-namespaced numeric code
//
// Do not manipulate these bits directly. Use the API functions such as
// wuffs_flate__status__is_error instead.
typedef int32_t wuffs_flate__status;

#define wuffs_flate__packageid 967230  // 0x000EC23E

#define WUFFS_FLATE__STATUS_OK 0                                   // 0x00000000
#define WUFFS_FLATE__ERROR_BAD_WUFFS_VERSION -2147483647           // 0x80000001
#define WUFFS_FLATE__ERROR_BAD_RECEIVER -2147483646                // 0x80000002
#define WUFFS_FLATE__ERROR_BAD_ARGUMENT -2147483645                // 0x80000003
#define WUFFS_FLATE__ERROR_INITIALIZER_NOT_CALLED -2147483644      // 0x80000004
#define WUFFS_FLATE__ERROR_INVALID_I_O_OPERATION -2147483643       // 0x80000005
#define WUFFS_FLATE__ERROR_CLOSED_FOR_WRITES -2147483642           // 0x80000006
#define WUFFS_FLATE__ERROR_UNEXPECTED_EOF -2147483641              // 0x80000007
#define WUFFS_FLATE__SUSPENSION_SHORT_READ 8                       // 0x00000008
#define WUFFS_FLATE__SUSPENSION_SHORT_WRITE 9                      // 0x00000009
#define WUFFS_FLATE__ERROR_CANNOT_RETURN_A_SUSPENSION -2147483638  // 0x8000000A

#define WUFFS_FLATE__ERROR_BAD_HUFFMAN_CODE_OVER_SUBSCRIBED \
  -1157040128  // 0xBB08F800
#define WUFFS_FLATE__ERROR_BAD_HUFFMAN_CODE_UNDER_SUBSCRIBED \
  -1157040127  // 0xBB08F801
#define WUFFS_FLATE__ERROR_BAD_HUFFMAN_CODE_LENGTH_COUNT \
  -1157040126  // 0xBB08F802
#define WUFFS_FLATE__ERROR_BAD_HUFFMAN_CODE_LENGTH_REPETITION \
  -1157040125                                            // 0xBB08F803
#define WUFFS_FLATE__ERROR_BAD_HUFFMAN_CODE -1157040124  // 0xBB08F804
#define WUFFS_FLATE__ERROR_BAD_HUFFMAN_MINIMUM_CODE_LENGTH \
  -1157040123                                                   // 0xBB08F805
#define WUFFS_FLATE__ERROR_BAD_DISTANCE -1157040122             // 0xBB08F806
#define WUFFS_FLATE__ERROR_BAD_DISTANCE_CODE_COUNT -1157040121  // 0xBB08F807
#define WUFFS_FLATE__ERROR_BAD_FLATE_BLOCK -1157040120          // 0xBB08F808
#define WUFFS_FLATE__ERROR_BAD_LITERAL_LENGTH_CODE_COUNT \
  -1157040119  // 0xBB08F809
#define WUFFS_FLATE__ERROR_INCONSISTENT_STORED_BLOCK_LENGTH \
  -1157040118  // 0xBB08F80A
#define WUFFS_FLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_HUFFMAN_DECODER_STATE \
  -1157040117  // 0xBB08F80B
#define WUFFS_FLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_HUFFMAN_END_OF_BLOCK \
  -1157040116  // 0xBB08F80C
#define WUFFS_FLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_DISTANCE \
  -1157040115  // 0xBB08F80D
#define WUFFS_FLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_N_BITS \
  -1157040114                                                     // 0xBB08F80E
#define WUFFS_FLATE__ERROR_MISSING_END_OF_BLOCK_CODE -1157040113  // 0xBB08F80F
#define WUFFS_FLATE__ERROR_NO_HUFFMAN_CODES -1157040112           // 0xBB08F810

bool wuffs_flate__status__is_error(wuffs_flate__status s);

const char* wuffs_flate__status__string(wuffs_flate__status s);

// ---------------- Public Consts

// ---------------- Structs

typedef struct {
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so. Instead, use the
  // wuffs_flate__flate_decoder__etc functions.
  //
  // In C++, these fields would be "private", but C does not support that.
  //
  // It is a struct, not a struct*, so that it can be stack allocated.
  struct {
    wuffs_flate__status status;
    uint32_t magic;

    uint32_t f_bits;
    uint32_t f_n_bits;
    uint32_t f_huffs[2][1234];
    uint32_t f_n_huffs_bits[2];
    uint8_t f_history[32768];
    uint32_t f_history_index;
    uint8_t f_code_lengths[320];
    bool f_end_of_block;

    struct {
      uint32_t coro_susp_point;
      wuffs_flate__status v_z;
      uint64_t v_n_copied;
      uint32_t v_already_full;
    } c_decode[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_final;
      uint32_t v_type;
    } c_decode_blocks[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_length;
      uint32_t v_n_copied;
      uint64_t scratch;
    } c_decode_uncompressed[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_i;
    } c_init_fixed_huffman[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_bits;
      uint32_t v_n_bits;
      uint32_t v_n_lit;
      uint32_t v_n_dist;
      uint32_t v_n_clen;
      uint32_t v_i;
      uint32_t v_mask;
      uint32_t v_table_entry;
      uint32_t v_table_entry_n_bits;
      uint32_t v_n_extra_bits;
      uint8_t v_rep_symbol;
      uint32_t v_rep_count;
    } c_init_dynamic_huffman[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_bits;
      uint32_t v_n_bits;
      uint32_t v_table_entry;
      uint32_t v_table_entry_n_bits;
      uint32_t v_lmask;
      uint32_t v_dmask;
      uint32_t v_redir_top;
      uint32_t v_redir_mask;
      uint32_t v_length;
      uint32_t v_distance;
      uint32_t v_n_copied;
      uint32_t v_hlen;
      uint32_t v_hdist;
    } c_decode_huffman_slow[1];
  } private_impl;
} wuffs_flate__flate_decoder;

// ---------------- Public Initializer Prototypes

// wuffs_flate__flate_decoder__initialize is an initializer function.
//
// It should be called before any other wuffs_flate__flate_decoder__* function.
//
// Pass WUFFS_VERSION and 0 for wuffs_version and for_internal_use_only.
void wuffs_flate__flate_decoder__initialize(wuffs_flate__flate_decoder* self,
                                            uint32_t wuffs_version,
                                            uint32_t for_internal_use_only);

// ---------------- Public Function Prototypes

wuffs_flate__status wuffs_flate__flate_decoder__decode(
    wuffs_flate__flate_decoder* self,
    wuffs_base__writer1 a_dst,
    wuffs_base__reader1 a_src);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // WUFFS_FLATE_H

// ---------------- END   USE "std/flate"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------- Status Codes

// Status codes are int32_t values:
//  - the sign bit indicates a non-recoverable status code: an error
//  - bits 10-30 hold the packageid: a namespace
//  - bits 8-9 are reserved
//  - bits 0-7 are a package-namespaced numeric code
//
// Do not manipulate these bits directly. Use the API functions such as
// wuffs_zlib__status__is_error instead.
typedef int32_t wuffs_zlib__status;

#define wuffs_zlib__packageid 2064249  // 0x001F7F79

#define WUFFS_ZLIB__STATUS_OK 0                                   // 0x00000000
#define WUFFS_ZLIB__ERROR_BAD_WUFFS_VERSION -2147483647           // 0x80000001
#define WUFFS_ZLIB__ERROR_BAD_RECEIVER -2147483646                // 0x80000002
#define WUFFS_ZLIB__ERROR_BAD_ARGUMENT -2147483645                // 0x80000003
#define WUFFS_ZLIB__ERROR_INITIALIZER_NOT_CALLED -2147483644      // 0x80000004
#define WUFFS_ZLIB__ERROR_INVALID_I_O_OPERATION -2147483643       // 0x80000005
#define WUFFS_ZLIB__ERROR_CLOSED_FOR_WRITES -2147483642           // 0x80000006
#define WUFFS_ZLIB__ERROR_UNEXPECTED_EOF -2147483641              // 0x80000007
#define WUFFS_ZLIB__SUSPENSION_SHORT_READ 8                       // 0x00000008
#define WUFFS_ZLIB__SUSPENSION_SHORT_WRITE 9                      // 0x00000009
#define WUFFS_ZLIB__ERROR_CANNOT_RETURN_A_SUSPENSION -2147483638  // 0x8000000A

#define WUFFS_ZLIB__ERROR_CHECKSUM_MISMATCH -33692672  // 0xFDFDE400
#define WUFFS_ZLIB__ERROR_INVALID_ZLIB_COMPRESSION_METHOD \
  -33692671  // 0xFDFDE401
#define WUFFS_ZLIB__ERROR_INVALID_ZLIB_COMPRESSION_WINDOW_SIZE \
  -33692670                                                    // 0xFDFDE402
#define WUFFS_ZLIB__ERROR_INVALID_ZLIB_PARITY_CHECK -33692669  // 0xFDFDE403
#define WUFFS_ZLIB__ERROR_TODO_UNSUPPORTED_ZLIB_PRESET_DICTIONARY \
  -33692668  // 0xFDFDE404

bool wuffs_zlib__status__is_error(wuffs_zlib__status s);

const char* wuffs_zlib__status__string(wuffs_zlib__status s);

// ---------------- Public Consts

// ---------------- Structs

typedef struct {
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so. Instead, use the
  // wuffs_zlib__adler32__etc functions.
  //
  // In C++, these fields would be "private", but C does not support that.
  //
  // It is a struct, not a struct*, so that it can be stack allocated.
  struct {
    wuffs_zlib__status status;
    uint32_t magic;

    uint32_t f_state;

  } private_impl;
} wuffs_zlib__adler32;

typedef struct {
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so. Instead, use the
  // wuffs_zlib__decoder__etc functions.
  //
  // In C++, these fields would be "private", but C does not support that.
  //
  // It is a struct, not a struct*, so that it can be stack allocated.
  struct {
    wuffs_zlib__status status;
    uint32_t magic;

    wuffs_flate__flate_decoder f_flate;
    wuffs_zlib__adler32 f_adler;

    struct {
      uint32_t coro_susp_point;
      uint16_t v_x;
      uint32_t v_checksum;
      wuffs_zlib__status v_z;
      uint64_t scratch;
    } c_decode[1];
  } private_impl;
} wuffs_zlib__decoder;

// ---------------- Public Initializer Prototypes

// wuffs_zlib__decoder__initialize is an initializer function.
//
// It should be called before any other wuffs_zlib__decoder__* function.
//
// Pass WUFFS_VERSION and 0 for wuffs_version and for_internal_use_only.
void wuffs_zlib__decoder__initialize(wuffs_zlib__decoder* self,
                                     uint32_t wuffs_version,
                                     uint32_t for_internal_use_only);

// ---------------- Public Function Prototypes

wuffs_zlib__status wuffs_zlib__decoder__decode(wuffs_zlib__decoder* self,
                                               wuffs_base__writer1 a_dst,
                                               wuffs_base__reader1 a_src);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // WUFFS_ZLIB_H

// C HEADER ENDS HERE.

#ifndef WUFFS_BASE_IMPL_H
#define WUFFS_BASE_IMPL_H

// Copyright 2017 The Wuffs Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// wuffs_base__empty_struct is used when a Wuffs function returns an empty
// struct. In C, if a function f returns void, you can't say "x = f()", but in
// Wuffs, if a function g returns empty, you can say "y = g()".
typedef struct {
} wuffs_base__empty_struct;

#define WUFFS_BASE__IGNORE_POTENTIALLY_UNUSED_VARIABLE(x) (void)(x)

// WUFFS_BASE__MAGIC is a magic number to check that initializers are called.
// It's not foolproof, given C doesn't automatically zero memory before use,
// but it should catch 99.99% of cases.
//
// Its (non-zero) value is arbitrary, based on md5sum("wuffs").
#define WUFFS_BASE__MAGIC (0x3CCB6C71U)

// WUFFS_BASE__ALREADY_ZEROED is passed from a container struct's initializer
// to a containee struct's initializer when the container has already zeroed
// the containee's memory.
//
// Its (non-zero) value is arbitrary, based on md5sum("zeroed").
#define WUFFS_BASE__ALREADY_ZEROED (0x68602EF1U)

// Use switch cases for coroutine suspension points, similar to the technique
// in https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
//
// We use trivial macros instead of an explicit assignment and case statement
// so that clang-format doesn't get confused by the unusual "case"s.
#define WUFFS_BASE__COROUTINE_SUSPENSION_POINT_0 case 0:;
#define WUFFS_BASE__COROUTINE_SUSPENSION_POINT(n) \
  coro_susp_point = n;                            \
  case n:;

#define WUFFS_BASE__COROUTINE_SUSPENSION_POINT_MAYBE_SUSPEND(n) \
  if (status < 0) {                                             \
    goto exit;                                                  \
  } else if (status == 0) {                                     \
    goto ok;                                                    \
  }                                                             \
  coro_susp_point = n;                                          \
  goto suspend;                                                 \
  case n:;

// Clang also defines "__GNUC__".
#if defined(__GNUC__)
#define WUFFS_BASE__LIKELY(expr) (__builtin_expect(!!(expr), 1))
#define WUFFS_BASE__UNLIKELY(expr) (__builtin_expect(!!(expr), 0))
#else
#define WUFFS_BASE__LIKELY(expr) (expr)
#define WUFFS_BASE__UNLIKELY(expr) (expr)
#endif

// Uncomment this #include for printf-debugging.
// #include <stdio.h>

// ---------------- Static Inline Functions
//
// The helpers below are functions, instead of macros, because their arguments
// can be an expression that we shouldn't evaluate more than once.
//
// They are in base-impl.h and hence copy/pasted into every generated C file,
// instead of being in some "base.c" file, since a design goal is that users of
// the generated C code can often just #include a single .c file, such as
// "gif.c", without having to additionally include or otherwise build and link
// a "base.c" file.
//
// They are static, so that linking multiple wuffs .o files won't complain about
// duplicate function definitions.
//
// They are explicitly marked inline, even if modern compilers don't use the
// inline attribute to guide optimizations such as inlining, to avoid the
// -Wunused-function warning, and we like to compile with -Wall -Werror.

static inline uint16_t wuffs_base__load_u16be(uint8_t* p) {
  return ((uint16_t)(p[0]) << 8) | ((uint16_t)(p[1]) << 0);
}

static inline uint16_t wuffs_base__load_u16le(uint8_t* p) {
  return ((uint16_t)(p[0]) << 0) | ((uint16_t)(p[1]) << 8);
}

static inline uint32_t wuffs_base__load_u32be(uint8_t* p) {
  return ((uint32_t)(p[0]) << 24) | ((uint32_t)(p[1]) << 16) |
         ((uint32_t)(p[2]) << 8) | ((uint32_t)(p[3]) << 0);
}

static inline uint32_t wuffs_base__load_u32le(uint8_t* p) {
  return ((uint32_t)(p[0]) << 0) | ((uint32_t)(p[1]) << 8) |
         ((uint32_t)(p[2]) << 16) | ((uint32_t)(p[3]) << 24);
}

static inline wuffs_base__slice_u8 wuffs_base__slice_u8__subslice_i(
    wuffs_base__slice_u8 s,
    uint64_t i) {
  if ((i <= SIZE_MAX) && (i <= s.len)) {
    return ((wuffs_base__slice_u8){
        .ptr = s.ptr + i,
        .len = s.len - i,
    });
  }
  return ((wuffs_base__slice_u8){});
}

static inline wuffs_base__slice_u8 wuffs_base__slice_u8__subslice_j(
    wuffs_base__slice_u8 s,
    uint64_t j) {
  if ((j <= SIZE_MAX) && (j <= s.len)) {
    return ((wuffs_base__slice_u8){.ptr = s.ptr, .len = j});
  }
  return ((wuffs_base__slice_u8){});
}

static inline wuffs_base__slice_u8 wuffs_base__slice_u8__subslice_ij(
    wuffs_base__slice_u8 s,
    uint64_t i,
    uint64_t j) {
  if ((i <= j) && (j <= SIZE_MAX) && (j <= s.len)) {
    return ((wuffs_base__slice_u8){
        .ptr = s.ptr + i,
        .len = j - i,
    });
  }
  return ((wuffs_base__slice_u8){});
}

// wuffs_base__slice_u8__prefix returns up to the first up_to bytes of s.
static inline wuffs_base__slice_u8 wuffs_base__slice_u8__prefix(
    wuffs_base__slice_u8 s,
    uint64_t up_to) {
  if ((uint64_t)(s.len) > up_to) {
    s.len = up_to;
  }
  return s;
}

// wuffs_base__slice_u8__suffix returns up to the last up_to bytes of s.
static inline wuffs_base__slice_u8 wuffs_base__slice_u8_suffix(
    wuffs_base__slice_u8 s,
    uint64_t up_to) {
  if ((uint64_t)(s.len) > up_to) {
    s.ptr += (uint64_t)(s.len) - up_to;
    s.len = up_to;
  }
  return s;
}

// wuffs_base__slice_u8__copy_from_slice calls memmove(dst.ptr, src.ptr,
// length) where length is the minimum of dst.len and src.len.
//
// Passing a wuffs_base__slice_u8 with all fields NULL or zero (a valid, empty
// slice) is valid and results in a no-op.
static inline uint64_t wuffs_base__slice_u8__copy_from_slice(
    wuffs_base__slice_u8 dst,
    wuffs_base__slice_u8 src) {
  size_t length = dst.len < src.len ? dst.len : src.len;
  if (length > 0) {
    memmove(dst.ptr, src.ptr, length);
  }
  return length;
}

static inline uint32_t wuffs_base__writer1__copy_from_history32(
    uint8_t** ptr_ptr,
    uint8_t* start,  // May be NULL, meaning an unmarked writer1.
    uint8_t* end,
    uint32_t distance,
    uint32_t length) {
  if (!start || !distance) {
    return 0;
  }
  uint8_t* ptr = *ptr_ptr;
  if ((size_t)(ptr - start) < (size_t)(distance)) {
    return 0;
  }
  start = ptr - distance;
  size_t n = end - ptr;
  if ((size_t)(length) > n) {
    length = n;
  } else {
    n = length;
  }
  // TODO: unrolling by 3 seems best for the std/flate benchmarks, but that is
  // mostly because 3 is the minimum length for the flate format. This function
  // implementation shouldn't overfit to that one format. Perhaps the
  // copy_from_history32 Wuffs method should also take an unroll hint argument,
  // and the cgen can look if that argument is the constant expression '3'.
  //
  // See also wuffs_base__writer1__copy_from_history32__bco below.
  //
  // Alternatively, or additionally, have a sloppy_copy_from_history32 method
  // that copies 8 bytes at a time, possibly writing more than length bytes?
  for (; n >= 3; n -= 3) {
    *ptr++ = *start++;
    *ptr++ = *start++;
    *ptr++ = *start++;
  }
  for (; n; n--) {
    *ptr++ = *start++;
  }
  *ptr_ptr = ptr;
  return length;
}

// wuffs_base__writer1__copy_from_history32__bco is a Bounds Check Optimized
// version of the wuffs_base__writer1__copy_from_history32 function above. The
// caller needs to prove that:
//  - start    != NULL
//  - distance != 0
//  - distance <= (*ptr_ptr - start)
//  - length   <= (end      - *ptr_ptr)
static inline uint32_t wuffs_base__writer1__copy_from_history32__bco(
    uint8_t** ptr_ptr,
    uint8_t* start,
    uint8_t* end,
    uint32_t distance,
    uint32_t length) {
  uint8_t* ptr = *ptr_ptr;
  start = ptr - distance;
  uint32_t n = length;
  for (; n >= 3; n -= 3) {
    *ptr++ = *start++;
    *ptr++ = *start++;
    *ptr++ = *start++;
  }
  for (; n; n--) {
    *ptr++ = *start++;
  }
  *ptr_ptr = ptr;
  return length;
}

static inline uint32_t wuffs_base__writer1__copy_from_reader32(
    uint8_t** ptr_wptr,
    uint8_t* wend,
    uint8_t** ptr_rptr,
    uint8_t* rend,
    uint32_t length) {
  uint8_t* wptr = *ptr_wptr;
  size_t n = length;
  if (n > wend - wptr) {
    n = wend - wptr;
  }
  uint8_t* rptr = *ptr_rptr;
  if (n > rend - rptr) {
    n = rend - rptr;
  }
  if (n > 0) {
    memmove(wptr, rptr, n);
    *ptr_wptr += n;
    *ptr_rptr += n;
  }
  return n;
}

static inline uint64_t wuffs_base__writer1__copy_from_slice(
    uint8_t** ptr_wptr,
    uint8_t* wend,
    wuffs_base__slice_u8 src) {
  uint8_t* wptr = *ptr_wptr;
  size_t n = src.len;
  if (n > wend - wptr) {
    n = wend - wptr;
  }
  if (n > 0) {
    memmove(wptr, src.ptr, n);
    *ptr_wptr += n;
  }
  return n;
}

static inline uint32_t wuffs_base__writer1__copy_from_slice32(
    uint8_t** ptr_wptr,
    uint8_t* wend,
    wuffs_base__slice_u8 src,
    uint32_t length) {
  uint8_t* wptr = *ptr_wptr;
  size_t n = src.len;
  if (n > length) {
    n = length;
  }
  if (n > wend - wptr) {
    n = wend - wptr;
  }
  if (n > 0) {
    memmove(wptr, src.ptr, n);
    *ptr_wptr += n;
  }
  return n;
}

// Note that the *__limit and *__mark methods are private (in base-impl.h) not
// public (in base-header.h). We assume that, at the boundary between user code
// and Wuffs code, the reader1 and writer1's private_impl fields (including
// limit and mark) are NULL. Otherwise, some internal assumptions break down.
// For example, limits could be represented as pointers, even though
// conceptually they are counts, but that pointer-to-count correspondence
// becomes invalid if a buffer is re-used (e.g. on resuming a coroutine).
//
// Admittedly, some of the Wuffs test code calls these methods, but that test
// code is still Wuffs code, not user code. Other Wuffs test code modifies
// private_impl fields directly.

static inline wuffs_base__reader1 wuffs_base__reader1__limit(
    wuffs_base__reader1* o,
    uint64_t* ptr_to_len) {
  wuffs_base__reader1 ret = *o;
  ret.private_impl.limit.ptr_to_len = ptr_to_len;
  ret.private_impl.limit.next = &o->private_impl.limit;
  return ret;
}

static inline wuffs_base__empty_struct wuffs_base__reader1__mark(
    wuffs_base__reader1* o,
    uint8_t* mark) {
  o->private_impl.mark = mark;
  return ((wuffs_base__empty_struct){});
}

// TODO: static inline wuffs_base__writer1 wuffs_base__writer1__limit()

static inline wuffs_base__empty_struct wuffs_base__writer1__mark(
    wuffs_base__writer1* o,
    uint8_t* mark) {
  o->private_impl.mark = mark;
  return ((wuffs_base__empty_struct){});
}

#endif  // WUFFS_BASE_IMPL_H

// ---------------- Status Codes Implementations

bool wuffs_zlib__status__is_error(wuffs_zlib__status s) {
  return s < 0;
}

const char* wuffs_zlib__status__strings0[11] = {
    "zlib: ok",
    "zlib: bad wuffs version",
    "zlib: bad receiver",
    "zlib: bad argument",
    "zlib: initializer not called",
    "zlib: invalid I/O operation",
    "zlib: closed for writes",
    "zlib: unexpected EOF",
    "zlib: short read",
    "zlib: short write",
    "zlib: cannot return a suspension",
};

const char* wuffs_zlib__status__strings1[5] = {
    "zlib: checksum mismatch",
    "zlib: invalid zlib compression method",
    "zlib: invalid zlib compression window size",
    "zlib: invalid zlib parity check",
    "zlib: TODO: unsupported zlib preset dictionary",
};

const char* wuffs_zlib__status__string(wuffs_zlib__status s) {
  const char** a = NULL;
  uint32_t n = 0;
  switch ((s >> 10) & 0x1FFFFF) {
    case 0:
      a = wuffs_zlib__status__strings0;
      n = 11;
      break;
    case wuffs_zlib__packageid:
      a = wuffs_zlib__status__strings1;
      n = 5;
      break;
  }
  uint32_t i = s & 0xFF;
  return i < n ? a[i] : "zlib: unknown status";
}

// ---------------- Private Consts

// ---------------- Private Initializer Prototypes

void wuffs_zlib__adler32__initialize(wuffs_zlib__adler32* self,
                                     uint32_t wuffs_version,
                                     uint32_t for_internal_use_only);

// ---------------- Private Function Prototypes

static uint32_t wuffs_zlib__adler32__update(wuffs_zlib__adler32* self,
                                            wuffs_base__slice_u8 a_x);

// ---------------- Initializer Implementations

void wuffs_zlib__adler32__initialize(wuffs_zlib__adler32* self,
                                     uint32_t wuffs_version,
                                     uint32_t for_internal_use_only) {
  if (!self) {
    return;
  }
  if (wuffs_version != WUFFS_VERSION) {
    self->private_impl.status = WUFFS_ZLIB__ERROR_BAD_WUFFS_VERSION;
    return;
  }
  if (for_internal_use_only != WUFFS_BASE__ALREADY_ZEROED) {
    memset(self, 0, sizeof(*self));
  }
  self->private_impl.magic = WUFFS_BASE__MAGIC;
  self->private_impl.f_state = 1;
}

void wuffs_zlib__decoder__initialize(wuffs_zlib__decoder* self,
                                     uint32_t wuffs_version,
                                     uint32_t for_internal_use_only) {
  if (!self) {
    return;
  }
  if (wuffs_version != WUFFS_VERSION) {
    self->private_impl.status = WUFFS_ZLIB__ERROR_BAD_WUFFS_VERSION;
    return;
  }
  if (for_internal_use_only != WUFFS_BASE__ALREADY_ZEROED) {
    memset(self, 0, sizeof(*self));
  }
  self->private_impl.magic = WUFFS_BASE__MAGIC;
  wuffs_flate__flate_decoder__initialize(
      &self->private_impl.f_flate, WUFFS_VERSION, WUFFS_BASE__ALREADY_ZEROED);
  wuffs_zlib__adler32__initialize(&self->private_impl.f_adler, WUFFS_VERSION,
                                  WUFFS_BASE__ALREADY_ZEROED);
}

// ---------------- Function Implementations

wuffs_zlib__status wuffs_zlib__decoder__decode(wuffs_zlib__decoder* self,
                                               wuffs_base__writer1 a_dst,
                                               wuffs_base__reader1 a_src) {
  if (!self) {
    return WUFFS_ZLIB__ERROR_BAD_RECEIVER;
  }
  if (self->private_impl.magic != WUFFS_BASE__MAGIC) {
    self->private_impl.status = WUFFS_ZLIB__ERROR_INITIALIZER_NOT_CALLED;
  }
  if (self->private_impl.status < 0) {
    return self->private_impl.status;
  }
  wuffs_zlib__status status = WUFFS_ZLIB__STATUS_OK;

  uint16_t v_x;
  uint32_t v_checksum;
  wuffs_zlib__status v_z;

  uint8_t* b_wptr_dst = NULL;
  uint8_t* b_wstart_dst = NULL;
  uint8_t* b_wend_dst = NULL;
  if (a_dst.buf) {
    b_wptr_dst = a_dst.buf->ptr + a_dst.buf->wi;
    b_wstart_dst = b_wptr_dst;
    b_wend_dst = b_wptr_dst;
    if (!a_dst.buf->closed) {
      uint64_t len = a_dst.buf->len - a_dst.buf->wi;
      wuffs_base__limit1* lim;
      for (lim = &a_dst.private_impl.limit; lim; lim = lim->next) {
        if (lim->ptr_to_len && (len > *lim->ptr_to_len)) {
          len = *lim->ptr_to_len;
        }
      }
      b_wend_dst += len;
    }
  }
  uint8_t* b_rptr_src = NULL;
  uint8_t* b_rstart_src = NULL;
  uint8_t* b_rend_src = NULL;
  if (a_src.buf) {
    b_rptr_src = a_src.buf->ptr + a_src.buf->ri;
    b_rstart_src = b_rptr_src;
    uint64_t len = a_src.buf->wi - a_src.buf->ri;
    wuffs_base__limit1* lim;
    for (lim = &a_src.private_impl.limit; lim; lim = lim->next) {
      if (lim->ptr_to_len && (len > *lim->ptr_to_len)) {
        len = *lim->ptr_to_len;
      }
    }
    b_rend_src = b_rptr_src + len;
  }

  uint32_t coro_susp_point = self->private_impl.c_decode[0].coro_susp_point;
  if (coro_susp_point) {
    v_x = self->private_impl.c_decode[0].v_x;
    v_checksum = self->private_impl.c_decode[0].v_checksum;
    v_z = self->private_impl.c_decode[0].v_z;
  }
  switch (coro_susp_point) {
    WUFFS_BASE__COROUTINE_SUSPENSION_POINT_0;

    {
      WUFFS_BASE__COROUTINE_SUSPENSION_POINT(1);
      uint16_t t_1;
      if (WUFFS_BASE__LIKELY(b_rend_src - b_rptr_src >= 2)) {
        t_1 = wuffs_base__load_u16be(b_rptr_src);
        b_rptr_src += 2;
      } else {
        self->private_impl.c_decode[0].scratch = 0;
        WUFFS_BASE__COROUTINE_SUSPENSION_POINT(2);
        while (true) {
          if (WUFFS_BASE__UNLIKELY(b_rptr_src == b_rend_src)) {
            goto short_read_src;
          }
          uint32_t t_0 = self->private_impl.c_decode[0].scratch & 0xFF;
          self->private_impl.c_decode[0].scratch >>= 8;
          self->private_impl.c_decode[0].scratch <<= 8;
          self->private_impl.c_decode[0].scratch |= ((uint64_t)(*b_rptr_src++))
                                                    << (64 - t_0);
          if (t_0 == 8) {
            t_1 = self->private_impl.c_decode[0].scratch >> (64 - 16);
            break;
          }
          t_0 += 8;
          self->private_impl.c_decode[0].scratch |= ((uint64_t)(t_0));
        }
      }
      v_x = t_1;
    }
    if (((v_x >> 8) & 15) != 8) {
      status = WUFFS_ZLIB__ERROR_INVALID_ZLIB_COMPRESSION_METHOD;
      goto exit;
    }
    if ((v_x >> 12) > 7) {
      status = WUFFS_ZLIB__ERROR_INVALID_ZLIB_COMPRESSION_WINDOW_SIZE;
      goto exit;
    }
    if ((v_x & 32) != 0) {
      status = WUFFS_ZLIB__ERROR_TODO_UNSUPPORTED_ZLIB_PRESET_DICTIONARY;
      goto exit;
    }
    if ((v_x % 31) != 0) {
      status = WUFFS_ZLIB__ERROR_INVALID_ZLIB_PARITY_CHECK;
      goto exit;
    }
    v_checksum = 0;
    while (true) {
      wuffs_base__writer1__mark(&a_dst, b_wptr_dst);
      {
        WUFFS_BASE__COROUTINE_SUSPENSION_POINT(3);
        if (a_dst.buf) {
          size_t n = b_wptr_dst - (a_dst.buf->ptr + a_dst.buf->wi);
          a_dst.buf->wi += n;
          wuffs_base__limit1* lim;
          for (lim = &a_dst.private_impl.limit; lim; lim = lim->next) {
            if (lim->ptr_to_len) {
              *lim->ptr_to_len -= n;
            }
          }
        }
        if (a_src.buf) {
          size_t n = b_rptr_src - (a_src.buf->ptr + a_src.buf->ri);
          a_src.buf->ri += n;
          wuffs_base__limit1* lim;
          for (lim = &a_src.private_impl.limit; lim; lim = lim->next) {
            if (lim->ptr_to_len) {
              *lim->ptr_to_len -= n;
            }
          }
        }
        wuffs_zlib__status t_2 = wuffs_flate__flate_decoder__decode(
            &self->private_impl.f_flate, a_dst, a_src);
        if (a_dst.buf) {
          b_wptr_dst = a_dst.buf->ptr + a_dst.buf->wi;
        }
        if (a_src.buf) {
          b_rptr_src = a_src.buf->ptr + a_src.buf->ri;
        }
        v_z = t_2;
      }
      v_checksum = wuffs_zlib__adler32__update(
          &self->private_impl.f_adler,
          ((wuffs_base__slice_u8){
              .ptr = a_dst.private_impl.mark,
              .len = a_dst.private_impl.mark
                         ? (size_t)(b_wptr_dst - a_dst.private_impl.mark)
                         : 0,
          }));
      if (v_z == 0) {
        goto label_0_break;
      }
      status = v_z;
      WUFFS_BASE__COROUTINE_SUSPENSION_POINT_MAYBE_SUSPEND(4);
    }
  label_0_break:;
    WUFFS_BASE__COROUTINE_SUSPENSION_POINT(5);
    uint32_t t_4;
    if (WUFFS_BASE__LIKELY(b_rend_src - b_rptr_src >= 4)) {
      t_4 = wuffs_base__load_u32be(b_rptr_src);
      b_rptr_src += 4;
    } else {
      self->private_impl.c_decode[0].scratch = 0;
      WUFFS_BASE__COROUTINE_SUSPENSION_POINT(6);
      while (true) {
        if (WUFFS_BASE__UNLIKELY(b_rptr_src == b_rend_src)) {
          goto short_read_src;
        }
        uint32_t t_3 = self->private_impl.c_decode[0].scratch & 0xFF;
        self->private_impl.c_decode[0].scratch >>= 8;
        self->private_impl.c_decode[0].scratch <<= 8;
        self->private_impl.c_decode[0].scratch |= ((uint64_t)(*b_rptr_src++))
                                                  << (64 - t_3);
        if (t_3 == 24) {
          t_4 = self->private_impl.c_decode[0].scratch >> (64 - 32);
          break;
        }
        t_3 += 8;
        self->private_impl.c_decode[0].scratch |= ((uint64_t)(t_3));
      }
    }
    if (v_checksum != t_4) {
      status = WUFFS_ZLIB__ERROR_CHECKSUM_MISMATCH;
      goto exit;
    }

    goto ok;
  ok:
    self->private_impl.c_decode[0].coro_susp_point = 0;
    goto exit;
  }

  goto suspend;
suspend:
  self->private_impl.c_decode[0].coro_susp_point = coro_susp_point;
  self->private_impl.c_decode[0].v_x = v_x;
  self->private_impl.c_decode[0].v_checksum = v_checksum;
  self->private_impl.c_decode[0].v_z = v_z;

exit:
  if (a_dst.buf) {
    size_t n = b_wptr_dst - (a_dst.buf->ptr + a_dst.buf->wi);
    a_dst.buf->wi += n;
    wuffs_base__limit1* lim;
    for (lim = &a_dst.private_impl.limit; lim; lim = lim->next) {
      if (lim->ptr_to_len) {
        *lim->ptr_to_len -= n;
      }
    }
    WUFFS_BASE__IGNORE_POTENTIALLY_UNUSED_VARIABLE(b_wstart_dst);
    WUFFS_BASE__IGNORE_POTENTIALLY_UNUSED_VARIABLE(b_wend_dst);
  }
  if (a_src.buf) {
    size_t n = b_rptr_src - (a_src.buf->ptr + a_src.buf->ri);
    a_src.buf->ri += n;
    wuffs_base__limit1* lim;
    for (lim = &a_src.private_impl.limit; lim; lim = lim->next) {
      if (lim->ptr_to_len) {
        *lim->ptr_to_len -= n;
      }
    }
    WUFFS_BASE__IGNORE_POTENTIALLY_UNUSED_VARIABLE(b_rstart_src);
    WUFFS_BASE__IGNORE_POTENTIALLY_UNUSED_VARIABLE(b_rend_src);
  }

  self->private_impl.status = status;
  return status;

short_read_src:
  if (a_src.buf && a_src.buf->closed && !a_src.private_impl.limit.ptr_to_len) {
    status = WUFFS_ZLIB__ERROR_UNEXPECTED_EOF;
    goto exit;
  }
  status = WUFFS_ZLIB__SUSPENSION_SHORT_READ;
  goto suspend;
}

static uint32_t wuffs_zlib__adler32__update(wuffs_zlib__adler32* self,
                                            wuffs_base__slice_u8 a_x) {
  uint32_t v_s1;
  uint32_t v_s2;
  wuffs_base__slice_u8 v_remaining;

  v_s1 = ((self->private_impl.f_state) & ((1 << (16)) - 1));
  v_s2 = ((self->private_impl.f_state) >> (32 - (16)));
  while (((uint64_t)(a_x.len)) > 0) {
    v_remaining = ((wuffs_base__slice_u8){});
    if (((uint64_t)(a_x.len)) > 5552) {
      v_remaining = wuffs_base__slice_u8__subslice_i(a_x, 5552);
      a_x = wuffs_base__slice_u8__subslice_j(a_x, 5552);
    }
    {
      wuffs_base__slice_u8 i_slice_p = a_x;
      uint8_t* v_p = i_slice_p.ptr;
      uint8_t* i_end0_p = i_slice_p.ptr + (i_slice_p.len / 8) * 8;
      while (v_p < i_end0_p) {
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
      }
      uint8_t* i_end1_p = i_slice_p.ptr + i_slice_p.len;
      while (v_p < i_end1_p) {
        v_s1 += ((uint32_t)(*v_p));
        v_s2 += v_s1;
        v_p++;
      }
    }
    v_s1 %= 65521;
    v_s2 %= 65521;
    a_x = v_remaining;
  }
  self->private_impl.f_state = (((v_s2 & 65535) << 16) | (v_s1 & 65535));
  return self->private_impl.f_state;
}
