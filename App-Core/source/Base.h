#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef bool b8;

typedef struct Vector2 v2;
typedef struct Vector3 v3;
typedef struct Vector4 v4;

#define GRAVITY 9.80665f

#define V2_FMT "<%.3f, %.3f>"
#define V3_FMT "<%.3f, %.3f, %.3f>"
#define V4_FMT "<%.3f, %.3f, %.3f, %.3f>"

#define V2_OPEN(v) v.x, v.y
#define V3_OPEN(v) v.x, v.y, v.z
#define V4_OPEN(v) v.x, v.y, v.z, v.w

#define V2_ZERO                                                                                                                                                                    \
    (v2)                                                                                                                                                                           \
    {                                                                                                                                                                              \
        0.f, 0.f                                                                                                                                                                   \
    }
#define V3_ZERO                                                                                                                                                                    \
    (v3)                                                                                                                                                                           \
    {                                                                                                                                                                              \
        0.f, 0.f, 0.f                                                                                                                                                              \
    }
#define V4_ZERO                                                                                                                                                                    \
    (v4)                                                                                                                                                                           \
    {                                                                                                                                                                              \
        0.f, 0.f, 0.f, 0.f                                                                                                                                                         \
    }

#define LEN(array) sizeof(array) / sizeof(array[0])
