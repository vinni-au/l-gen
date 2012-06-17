/*
 * Copyright (C) 2007, libMAFSA development team.
 *
 * This file is released under the LGPL.
 */

#ifndef __MAFSA_MAFSA_INTERNAL_H__
#define __MAFSA_MAFSA_INTERNAL_H__

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BEOS__) && !defined(__CYGWIN__)
#define MAFSA_USE_MSC_EXTENSIONS 1
#endif

#ifndef MAFSACALL
#if defined(MAFSA_USE_MSC_EXTENSIONS)
#define MAFSACALL __cdecl
#elif defined(__GNUC__) && defined(__i386)
#define MAFSACALL __attribute__((cdecl))
#else
#define MAFSACALL
#endif
#endif /* MAFSACALL */

#ifdef _WIN32
typedef unsigned char u_int8_t;
typedef unsigned int u_int32_t;
typedef unsigned short u_int16_t;
typedef unsigned long long u_int64_t;
typedef unsigned int size_t;
typedef unsigned int uint;
typedef size_t ssize_t;
typedef int int32_t;
typedef long long int64_t;
typedef u_int8_t uint8_t;
typedef u_int32_t uint32_t;
typedef u_int16_t uint16_t;
typedef u_int64_t uint64_t;
typedef u_int8_t MAFSA_letter;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MAFSA_MAFSA_INTERNAL_H__ */

