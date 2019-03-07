// RUN: %clang_cc1 -triple x86_64-apple-macosx10.13.0-wine32 -emit-llvm -o - %s | FileCheck %s

@interface Foo {
  signed char _bar;
}

@property(readonly) signed char bar;

@end

@implementation Foo

@synthesize bar = _bar;
// CHECK: %[[IVAR:.*]] = load i64, i64* @"OBJC_IVAR_$_Foo._bar", align 8
// CHECK: %[[IVAR_PTR:.*]] = getelementptr inbounds i8, i8* %{{.*}}, i64 %[[IVAR]]
// CHECK: %[[VAL:.*]] = load atomic i8, i8* %[[IVAR_PTR]] unordered, align 1
// CHECK: ret i8 %[[VAL]]

@end
