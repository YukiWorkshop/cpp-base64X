#ifdef __SSSE3__
#define HAVE_SSSE3                 1
#else
#define HAVE_SSSE3                 0
#endif

#ifdef __SSE4_1__
#define HAVE_SSE41                 1
#else
#define HAVE_SSE41                 0
#endif

#ifdef __SSE4_2__
#define HAVE_SSE42                 1
#else
#define HAVE_SSE42                 0
#endif

#ifdef __AVX__
#define HAVE_AVX                   1
#else
#define HAVE_AVX                   0
#endif

#ifdef __AVX2__
#define HAVE_AVX2                  1
#else
#define HAVE_AVX2                  0
#endif

#ifdef __ARM_NEON
#define HAVE_NEON32                1
#else
#define HAVE_NEON32                0
#endif

#ifndef HAVE_NEON64
#define HAVE_NEON64                0
#endif

#ifndef HAVE_FAST_UNALIGNED_ACCESS
#define HAVE_FAST_UNALIGNED_ACCESS 0
#endif
