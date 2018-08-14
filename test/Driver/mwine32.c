// RUN: %clang -### -target x86_64-apple-darwin17 -mwine32 -c %s 2>&1 | FileCheck %s
// RUN: %clang -### -target i386-apple-darwin17 -mwine32 -c %s 2>&1 FileCheck %s

// CHECK: Target: x86_64-apple-darwin17-wine32
// CHECK: "-triple" "x86_64-apple-macosx10.13.0-wine32"
