// RUN: %clang -### -target x86_64-apple-darwin17 -mwine32 -c %s 2>&1 | FileCheck %s
// RUN: %clang -### -target i386-apple-darwin17 -mwine32 -c %s 2>&1 | FileCheck %s
// RUN: %clang -### -target x86_64-apple-darwin17 -mwine32 -mdefault-address-space=ptr32 -mstorage-address-space=default -msystem-address-space=ptr32 -minterop64-32-thunk-prefix=__wine32_ -minterop64-32-cs32-name=__wine32_cs32 -minterop64-32-cs64-name=__wine32_cs64 -c %s 2>&1 | FileCheck -check-prefix=CHECK-OVER %s

// CHECK: Target: x86_64-apple-darwin17-wine32
// CHECK: "-triple" "x86_64-apple-macosx10.13.0-wine32"
// CHECK-SAME: "-mstorage-address-space=ptr32"

// CHECK-OVER: Target: x86_64-apple-darwin17-wine32
// CHECK-OVER: "-triple" "x86_64-apple-macosx10.13.0-wine32"
// CHECK-OVER-SAME: "-mdefault-address-space=ptr32"
// CHECK-OVER-SAME: "-mstorage-address-space=default"
// CHECK-OVER-SAME: "-msystem-address-space=ptr32"
// CHECK-OVER-SAME: "-minterop64-32-thunk-prefix=__wine32_"
// CHECK-OVER-SAME: "-minterop64-32-cs32-name=__wine32_cs32"
// CHECK-OVER-SAME: "-minterop64-32-cs64-name=__wine32_cs64"
