// RUN: %clang_cc1 -triple x86_64-apple-macosx10.13.0-wine32 -mdefault-address-space=ptr32 -isystem %S/Inputs -fsyntax-only -verify %s

#include <ptr32-system-as.h>

extern void * p32;
extern void * __ptr64 p64;

_Static_assert(sizeof(void *) == 4, "__ptr32 should be 4 bytes long!");
_Static_assert(_Alignof(void *) == 4, "__ptr32 should be aligned to 4 bytes!");
_Static_assert(sizeof(void * __ptr64) == 8, "__ptr64 should be 8 bytes long!");
_Static_assert(_Alignof(void * __ptr64) == 8, "__ptr64 should be aligned to 8 bytes!");
_Static_assert(sizeof(p32) == 4, "__ptr32 should be 4 bytes long!");
_Static_assert(sizeof(&p32) == 4, "__ptr32 should be 4 bytes long!");

_Static_assert(sizeof(system_pointer) == 8, "Pointer from system header should be 8 bytes long!");
_Static_assert(_Alignof(system_pointer) == 8, "Pointer from system header should be aligned to 8 bytes!");

#pragma clang default_addr_space(push, default)

_Static_assert(sizeof(void *) == 8, "__ptr64 should be 8 bytes long!");
_Static_assert(_Alignof(void *) == 8, "__ptr64 should be aligned to 8 bytes!");
_Static_assert(sizeof(p64) == 8, "__ptr64 should be 8 bytes long!");

#pragma clang default_addr_space()

_Static_assert(sizeof(void *) == 4, "__ptr32 should be 4 bytes long!");
_Static_assert(_Alignof(void *) == 4, "__ptr32 should be aligned to 4 bytes!");

void foo() {
  void *p = p64;
  // expected-error@-1{{initializing 'void *' with an expression of type 'void * __ptr64 ' changes address space of pointer}}
  p = p32;  // no-warning
  p32 = p64;
  // expected-error@-1{{assigning 'void * __ptr64 ' to 'void *' changes address space of pointer}}
}
