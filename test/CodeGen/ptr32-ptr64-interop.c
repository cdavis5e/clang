// RUN: %clang_cc1 -triple x86_64-apple-macosx10.13.0-wine32 -O2 -emit-llvm -o - %s | FileCheck %s

void foo(int * __ptr32 a, void (* __ptr32 b)(int, int * __ptr32, int *)) {
  int c;
  b(*a, &c, &c);
  // CHECK-LABEL: @foo(i32 addrspace(32)*{{.*}} %a, void (i32, i32 addrspace(32)*, i32*) addrspace(32)*{{.*}} %b)
  // CHECK: %[[VAL:[0-9a-zA-Z_]*]] = load i32, i32 addrspace(32)* %a
  // CHECK: call addrspace(32) void %b(i32 %[[VAL]], i32 addrspace(32)* {{.*}}, i32* {{.*}}){{.*}}
}

void (__attribute__((stdcall32)) * __ptr32 pbar)(int, int * __ptr32);
void (__attribute__((stdcall32)) * __ptr32 pbaz)(int, int * __ptr32);

extern void __attribute__((stdcall32)) bar(int, int * __ptr32);

#pragma clang ptr32_thunk_prefix("__wine32_")
extern void __attribute__((stdcall32)) baz(int, int * __ptr32);

void quux(void) {
  pbar = bar;
  pbaz = baz;
  // CHECK-LABEL: @quux()
  // CHECK: @__i386_on_x86_64_thunk32_bar
  // CHECK: @__wine32_thunk32_baz
}
