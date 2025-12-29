#pragma once

#if defined(__x86_64__) && (defined(__AVX2__) || defined(__SSE2__))
#include <immintrin.h>
#ifdef __AVX2__
#define USE_AVX2
#define MATRIX_ALIGNMENT 32
#else
#define USE_SSE2
#define MATRIX_ALIGNMENT 16
#endif
#else
#define MATRIX_ALIGNMENT 4
#endif