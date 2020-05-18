#pragma once

#define PLATFORM_WINDOWS 0
#define PLATFORM_LINUX 1
#define PLATFORM_OSX 2

#define UI_WIN32 0
#define UI_XLIB 1

#if defined(_WIN32)
#include <Windows.h>
#include <cstdint>

#define PROVOX_PLATFORM PLATFORM_WINDOWS
#elif defined(__linux__)
#error "Linux is not yet supported"

#define PROVOX_PLATFORM PLATFORM_LINUX
#elif defined(__APPLE__)
#error "MacOS is not yet supported"

#define PROVOX_PLATFORM PLATFORM_OSX
#else
#error "Unsupported operating system"
#endif

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uintptr_t uintptr;
typedef intptr_t intptr;
