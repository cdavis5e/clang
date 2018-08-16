// RUN: %clang_cc1 -triple x86_64-apple-macosx10.13.0-wine32 -fsyntax-only -verify %s

extern void * __ptr32 p32;
extern void * __ptr64 p64;

_Static_assert(sizeof(void * __ptr32) == 4, "__ptr32 should be 4 bytes long!");
_Static_assert(_Alignof(void * __ptr32) == 4, "__ptr32 should be aligned to 4 bytes!");
_Static_assert(sizeof(void * __ptr64) == 8, "__ptr64 should be 8 bytes long!");
_Static_assert(_Alignof(void * __ptr64) == 8, "__ptr64 should be aligned to 8 bytes!");

extern void bar(int * __ptr32);
extern void baz(int *);

void foo() {
  void *p = p64;  // no-warning
  // It should be possible to convert 32->64...
  p = p32;  // no-warning
  // ...but not 64->32.
  p32 = p64;
  // expected-error@-1{{assigning 'void * __ptr64' to 'void * __ptr32' changes address space of pointer}}
  // By default, stack variables in this environment are placed in the low
  // 4 GB (i.e. they're __ptr32). Test that we can pass addresses of stack
  // variables around as though they were __ptr32.
  int x;
  bar(&x);  // no-warning
  baz(&x);  // no-warning
}
