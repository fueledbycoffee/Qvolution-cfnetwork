#ifndef IMP_SYSTEM_CF_TYPES_H
#define IMP_SYSTEM_CF_TYPES_H
#include <stddef.h>
/* Opaque types only: native control does not emulate CoreFoundation objects. */
typedef const void *CFAllocatorRef;
typedef const void *CFURLRef;
typedef const void *CFStringRef;
typedef const void *CFReadStreamRef;
typedef const void *CFWriteStreamRef;
#endif
