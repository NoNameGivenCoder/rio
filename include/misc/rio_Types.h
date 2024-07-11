#ifndef RIO_TYPES_H
#define RIO_TYPES_H

/*
#if !(defined(_WIN32) || defined(__WUT__))
    #error "Unknown host platform."
#endif
*/
#if !(defined(RIO_DEBUG) || defined(RIO_RELEASE))
    #error "Build target is not defined."
#elif (defined(RIO_DEBUG) && defined(RIO_RELEASE))
    #error "Multiple build targets defined."
#endif

#if defined(RIO_DEBUG)
    #define RIO_FORCE_INLINE inline
#else
    #define RIO_FORCE_INLINE __attribute__((always_inline)) inline
#endif

#if defined(__WUT__)
    #define RIO_IS_WIN  0
    #define RIO_IS_CAFE 1
#else
    #define RIO_IS_WIN  1
    #define RIO_IS_CAFE 0
#endif

#ifdef __cplusplus
    #include <cstdint>
    #include <cstddef>
    #include <cassert>
#else
    #include <stdint.h>
    #include <stddef.h>
    #include <assert.h>
    #include <stdbool.h>
#endif

typedef  int8_t s8;
typedef uint8_t u8;

typedef  int16_t s16;
typedef uint16_t u16;

typedef  int32_t s32;
typedef uint32_t u32;

typedef  int64_t s64;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

static_assert(sizeof(s8)  == sizeof(u8)  && sizeof(u8)  == sizeof(char) && sizeof(char) == 1);
static_assert(sizeof(s16) == sizeof(u16) && sizeof(u16) == 2);
static_assert(sizeof(s32) == sizeof(u32) && sizeof(u32) == 4);
static_assert(sizeof(s64) == sizeof(u64) && sizeof(u64) == 8);
static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);

#if !RIO_IS_CAFE && !defined(BOOL) && !defined(_MSC_VER)
    #define BOOL int
#endif

#ifdef RIO_DEBUG
    #if RIO_IS_WIN
        #define RIO_ASSERT(ARG) assert(ARG)

        #ifdef __cplusplus
            #include <cstdio>
        #else
            #include <stdio.h>
        #endif
        #ifdef _MSC_VER
            #define RIO_LOG(FMT, ...) printf(FMT, __VA_ARGS__)
        #else
            #define RIO_LOG(FMT, ARGS...) printf(FMT, ##ARGS)
        #endif

    #elif RIO_IS_CAFE
        #include <coreinit/debug.h>

        #define RIO_ASSERT(ARG)                         \
            do                                          \
            {                                           \
                if (!(ARG))                             \
                    OSPanic(__FILE__, __LINE__, #ARG);  \
            } while (0)

        #define RIO_LOG(FMT, ARGS...) OSReport(FMT, ## ARGS)
    #endif
#else
    #define RIO_ASSERT(ARG)
    #define RIO_LOG(FMT, ARGS...)
#endif // RIO_DEBUG

#endif // RIO_TYPES_H
