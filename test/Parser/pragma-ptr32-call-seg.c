// RUN: %clang_cc1 -triple x86_64-apple-macosx10.13.0-wine32 -fsyntax-only -verify %s

#pragma clang ptr32_call_seg
// expected-warning@-1{{missing '(' after '#pragma clang ptr32_call_seg'}}

#pragma clang ptr32_call_seg(foo)
// expected-warning@-1{{expected integer between 0 and 65535 inclusive}}

#pragma clang ptr32_call_seg(0x10000)
// expected-warning@-1{{expected integer between 0 and 65535 inclusive}}

#pragma clang ptr32_call_seg(0x1003)
#pragma clang ptr32_call_seg(0)

#pragma clang ptr32_call_seg(0
// expected-warning@-1{{missing ')' after '#pragma clang ptr32_call_seg'}}
