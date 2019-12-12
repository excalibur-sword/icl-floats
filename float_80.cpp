#include "float_80.h"

using f80 = float_80_t;

// Unary Minus
__declspec(noinline) __declspec(nothrow) f80 float_80_t::operator -(void) const {
  __asm {
    mov rax, [rcx]
    mov [rdx], rax
    mov ax, [rcx + 4*2]
    xor ax, 8000h
    mov [rdx + 4*2], ax
  }
}

// Additions
__declspec(noinline) f80 operator +(const f80 &, const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fld tbyte ptr [r8]
    faddp st(1), st(0)
    fstp tbyte ptr [rcx]
  }
}
// Subtractions
__declspec(noinline) f80 operator -(const f80 &, const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fld tbyte ptr [r8]
    fsubp st(1), st(0)
    fstp tbyte ptr [rcx]
  }
}
// Multiplications
__declspec(noinline) f80 operator *(const f80 &, const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fld tbyte ptr [r8]
    fmulp st(1), st(0)
    fstp tbyte ptr [rcx]
  }
}
// Divisions
__declspec(noinline) f80 operator /(const f80 &, const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fld tbyte ptr [r8]
    fdivp st(1), st(0)
    fstp tbyte ptr [rcx]
  }
}

// Absolute value
__declspec(noinline) f80 Abs(const f80 &) {
  __asm {
    mov rax, [rdx]
    mov[rcx], rax
    mov ax, [rdx + 4*2]
    and ax, 7fffh
    mov[rcx + 4*2], ax
  }
}

// Reciprocal estimation
__declspec(noinline) f80 Rcp(const f80 &) {
  __asm {
    fld1
    fld tbyte ptr [rdx]
    fdivp st(1), st(0)
    fstp tbyte ptr [rcx]
  }
}

// Square root
__declspec(noinline) f80 Sqrt(const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fsqrt
    fstp tbyte ptr [rcx]
  }
}

// Trigonometric
__declspec(noinline) f80 Sin(const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fsin
    fstp tbyte ptr [rcx]
  }
}
__declspec(noinline) f80 Cos(const f80 &) {
  __asm {
    fld tbyte ptr [rdx]
    fcos
    fstp tbyte ptr [rcx]
  }
}

// Logarithmic
__declspec(noinline) f80 Ln(const f80 &) {
  __asm {
    fldln2
    fld tbyte ptr [rdx]
    fyl2x
    fstp tbyte ptr [rcx]
  }
}
__declspec(noinline) f80 Log2(const f80 &) {
  __asm {
    fld1
    fld tbyte ptr [rdx]
    fyl2x
    fstp tbyte ptr [rcx]
  }
}
__declspec(noinline) f80 Log10(const f80 &) {
  __asm {
    fldlg2
    fld tbyte ptr [rdx]
    fyl2x
    fstp tbyte ptr [rcx]
  }
}
