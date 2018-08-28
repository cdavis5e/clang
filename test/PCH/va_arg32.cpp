// Test this without pch.
// RUN: %clang_cc1 -triple=x86_64-unknown-freebsd7.0-wine32 -include %S/Inputs/va_arg.h %s -emit-llvm-only
// REQUIRES: x86-registered-target

// Test with pch.
// RUN: %clang_cc1 -triple=x86_64-unknown-freebsd7.0-wine32 -emit-pch -x c++-header -o %t %S/Inputs/va_arg.h
// RUN: %clang_cc1 -triple=x86_64-unknown-freebsd7.0-wine32 -include-pch %t %s -emit-llvm-only

typedef __SIZE_TYPE__ size_t;

extern "C" {
int vsnprintf(char * , size_t, const char * , va_list) ;
int __attribute__((ms_abi)) wvsprintfA(char *, const char *, __ms_va_list);
int __attribute__((cdecl32)) wvsprintfA32(char *, const char *, __va_list32);
}

void f(char *buffer, unsigned count, const char* format, va_list argptr) {
  vsnprintf(buffer, count, format, argptr);
}

void g(char *buffer, const char *format, __ms_va_list argptr) {
  wvsprintfA(buffer, format, argptr);
}

void h(char *buffer, const char *format, __va_list32 argptr) {
  wvsprintfA32(buffer, format, argptr);
}
