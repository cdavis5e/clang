// RUN: %clang_cc1 -triple x86_64-apple-macosx10.13.0-wine32 -O2 -emit-llvm -o - %s | FileCheck %s

#pragma clang ptr32_call_seg(0x0f00)

void foo(int * __ptr32 a, void (* __ptr32 b)(int)) {
  b(*a);
  // CHECK-LABEL: @foo(i32 addrspace(32)*{{.*}} %a, void (i32) addrspace(32)*{{.*}} %b)
  // CHECK: %[[VAL:[0-9a-zA-Z_]*]] = load i32, i32 addrspace(32)* %a
  // CHECK: call addrspace(32) void %b(i32 %[[VAL]]){{.*}} #[[ATTR:[0-9]+]]
}

// CHECK: attributes #[[ATTR]] = { {{.*}}"based-far-segment"="0xF00"{{.*}} }
