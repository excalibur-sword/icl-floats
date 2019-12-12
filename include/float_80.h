#ifndef _62BC6D80_639F_42AC_A4E3_BDC7085266CC
#define _62BC6D80_639F_42AC_A4E3_BDC7085266CC

#if !defined(__INTEL_COMPILER)
#error Intel C++ compiler required.
#endif

inline void fpu_set_cw(const unsigned int &cw) {
  __asm {
    fnclex
    mov rcx, cw
    fldcw word ptr [rcx]
  }
}

class float_80_t {
  // bitmap
  //  fraction : 63; // fractional part
  //  one      :  1; // always 1 if nonzero and normal
  //  exponent : 15; // exponent + 0x3FFF
  //  sign     :  1; // sign bit
  unsigned short int x[5];

public:
  inline __declspec(nothrow) ~float_80_t(void) = default;
  inline __declspec(nothrow) float_80_t(void) {}
  inline float_80_t(const int &v) {
    __asm {
      fnclex
      mov rdx, v
      mov rcx, this
      fild dword ptr[rdx]
      fstp tbyte ptr[rcx]
    }
  }
  inline float_80_t(const double &v) {
    __asm {
      fnclex
      mov rdx, v
      mov rcx, this
      fld qword ptr [rdx]
      fstp tbyte ptr [rcx]
    }
  }
  inline __declspec(nothrow) float_80_t(
    unsigned short int v0,
    unsigned short int v1,
    unsigned short int v2,
    unsigned short int v3,
    unsigned short int v4
  ) {
    this->x[0] = v0;
    this->x[1] = v1;
    this->x[2] = v2;
    this->x[3] = v3;
    this->x[4] = v4;
  }
  float_80_t(float_80_t const &) = default;

  inline __declspec(nothrow) unsigned short int x0(void) const { return this->x[0]; }
  inline __declspec(nothrow) unsigned short int x1(void) const { return this->x[1]; }
  inline __declspec(nothrow) unsigned short int x2(void) const { return this->x[2]; }
  inline __declspec(nothrow) unsigned short int x3(void) const { return this->x[3]; }
  inline __declspec(nothrow) unsigned short int x4(void) const { return this->x[4]; }

  inline double ToDouble(void) const {
    double r;
    __asm {
      mov rcx, this
      lea rdx, r
      fld tbyte ptr [rcx]
      fstp qword ptr [rdx]
    }
    return r;
  }

  // Assignments
  inline __declspec(nothrow) float_80_t & operator =(const double &rh) {
    __asm {
      mov rdx, rh
      mov rcx, this
      fld qword ptr [rdx]
      fstp tbyte ptr [rcx]
    }
  }
  float_80_t & operator =(const float_80_t &) = default;

  // Unary Minus
  __declspec(noinline) __declspec(nothrow) float_80_t operator -(void) const;

  // Self-Additions
  inline float_80_t & operator +=(const float_80_t &rh) {
    __asm {
      mov rcx, this
      mov rdx, rh
      fld tbyte ptr [rcx]
      fld tbyte ptr [rdx]
      faddp st(1), st(0)
      fstp tbyte ptr [rcx]
    }
  }
  // Self-Subtractions
  inline float_80_t & operator -=(const float_80_t &rh) {
    __asm {
      mov rcx, this
      mov rdx, rh
      fld tbyte ptr [rcx]
      fld tbyte ptr [rdx]
      fsubp st(1), st(0)
      fstp tbyte ptr [rcx]
    }
  }
  // Self-Multiplications
  inline float_80_t & operator *=(const float_80_t &rh) {
    __asm {
      mov rcx, this
      mov rdx, rh
      fld tbyte ptr [rcx]
      fld tbyte ptr [rdx]
      fmulp st(1), st(0)
      fstp tbyte ptr [rcx]
    }
  }
  // Self-Divisions
  inline float_80_t & operator /=(const float_80_t &rh) {
    __asm {
      mov rcx, this
      mov rdx, rh
      fld tbyte ptr [rcx]
      fld tbyte ptr [rdx]
      fdivp st(1), st(0)
      fstp tbyte ptr [rcx]
    }
  }

  // Equality Comparisons
  inline __declspec(nothrow) bool operator ==(const float_80_t &rh) const {
    return (
      this->x[0] == rh.x[0] &&
      this->x[1] == rh.x[1] &&
      this->x[2] == rh.x[2] &&
      this->x[3] == rh.x[3] &&
      this->x[4] == rh.x[4]
    );
  }
  // Not-Equal-To Comparisons
  inline __declspec(nothrow) bool operator !=(const float_80_t &rh) const {
    return (
      this->x[0] != rh.x[0] ||
      this->x[1] != rh.x[1] ||
      this->x[2] != rh.x[2] ||
      this->x[3] != rh.x[3] ||
      this->x[4] != rh.x[4]
    );
  }
  // Greater-Than Comparisons
  inline bool operator >(const float_80_t &rh) const {
    __asm {
      mov rdx, rh
      mov rcx, this
      fld tbyte ptr [rdx]
      fld tbyte ptr [rcx]
      fcomip st(0), st(1)
      seta al
      fstp st(0)
    }
  }
  // Less-Than Comparisons
  inline bool operator <(const float_80_t &rh) const {
    __asm {
      mov rdx, rh
      mov rcx, this
      fld tbyte ptr [rdx]
      fld tbyte ptr [rcx]
      fcomip st(0), st(1)
      setc al
      fstp st(0)
    }
  }
  // Greater-Than-Or-Equal-To Comparisons
  inline bool operator >=(const float_80_t &rh) const {
    __asm {
      mov rdx, rh
      mov rcx, this
      fld tbyte ptr [rdx]
      fld tbyte ptr [rcx]
      fcomip st(0), st(1)
      setnc al
      fstp st(0)
    }
  }
  // Less-Than-Or-Equal-To Comparisons
  inline bool operator <=(const float_80_t &rh) const {
    __asm {
      mov rdx, rh
      mov rcx, this
      fld tbyte ptr [rdx]
      fld tbyte ptr [rcx]
      fcomip st(0), st(1)
      setbe al
      fstp st(0)
    }
  }

  // Micellaneous
  inline __declspec(nothrow) bool IsZero(void) const {
    return (
      0 == this->x[0] &&
      0 == this->x[1] &&
      0 == this->x[2] &&
      0 == this->x[3] &&
      0 == (this->x[4] & 0x7fffu)
    );
  }
  inline __declspec(nothrow) bool IsOne(void) const {
    return (
      0 == this->x[0] &&
      0 == this->x[1] &&
      0 == this->x[2] &&
      0x8000u == this->x[3] &&
      0x3fffu == this->x[4]
    );
  }
  inline __declspec(nothrow) bool IsPositive(void) const {
    return (0 == (this->x[4] & 0x8000u));
  }
  inline __declspec(nothrow) bool IsNegative(void) const {
    return (0 != (this->x[4] & 0x8000u));
  }
  inline __declspec(nothrow) bool IsInfinite(void) const {
    return (0 != (this->x[3] & 0x8000u) && 0x7fffu == (this->x[4] & 0x7fffu));
  }
  inline __declspec(nothrow) bool IsQNaN(void) const {
    return (0xc000u == (this->x[3] & 0xc000u) && 0x7fffu == (this->x[4] & 0x7fffu));
  }
}; // float_80_t

// mathematical constants
const float_80_t F80_LOG2_E = {0xf0bcu, 0x5c17u, 0x3b29u, 0xb8aau, 0x3fffu}; // log2(e)
const float_80_t F80_LN2 = {0x79acu, 0xd1cfu, 0x17f7u, 0xb172u, 0x3ffeu}; // ln(2)
const float_80_t F80_LOG2_10 = {0x8afeu, 0xcd1bu, 0x784bu, 0xd49au, 0x4000u}; // log2(10)
const float_80_t F80_LOG10_2 = {0xf799u, 0xfbcfu, 0x9a84u, 0x9a20u, 0x3ffdu}; // log10(2)
const float_80_t F80_PI = {0xc235u, 0x2168u, 0xdaa2u, 0xc90fu, 0x4000u}; // pi

// limits
const float_80_t F80_EPS = {0, 0, 0, 0x8000u, 0x3fc0u}; // epsilon
const float_80_t F80_MAX = {0xffffu, 0xffffu, 0xffffu, 0xffffu, 0x7ffeu}; // maximum
const float_80_t F80_MIN = {0, 0, 0, 0x8000u, 0x0001u}; // minimum
const int F80_DIG = 18;

// Equality Comparisons
inline bool operator ==(const int &lh, const float_80_t &rh) {return rh == lh;}
inline bool operator ==(const double &lh, const float_80_t &rh) {return rh == lh;}
// Not-Equal-To Comparisons
inline bool operator !=(const int &lh, const float_80_t &rh) {return rh != lh;}
inline bool operator !=(const double &lh, const float_80_t &rh) {return rh != lh;}
// Greater-Than Comparisons
inline bool operator >(const int &lh, const float_80_t &rh) {return rh < lh;}
inline bool operator >(const double &lh, const float_80_t &rh) {return rh < lh;}
// Less-Than Comparisons
inline bool operator <(const int &lh, const float_80_t &rh) { return rh > lh; }
inline bool operator <(const double &lh, const float_80_t &rh) { return rh > lh; }
// Greater-Than-Or-Equal-To Comparisons
inline bool operator >=(const int &lh, const float_80_t &rh) {return rh <= lh;}
inline bool operator >=(const double &lh, const float_80_t &rh) {return rh <= lh;}
// Less-Than-Or-Equal-To Comparisons
inline bool operator <=(const int &lh, const float_80_t &rh) { return rh >= lh; }
inline bool operator <=(const double &lh, const float_80_t &rh) { return rh >= lh; }

// Additions
__declspec(noinline) float_80_t operator +(const float_80_t &, const float_80_t &);
// Subtractions
__declspec(noinline) float_80_t operator -(const float_80_t &, const float_80_t &);
// Multiplications
__declspec(noinline) float_80_t operator *(const float_80_t &, const float_80_t &);
// Divisions
__declspec(noinline) float_80_t operator /(const float_80_t &, const float_80_t &);

// Absolute value
__declspec(noinline) float_80_t Abs(const float_80_t &);
// Reciprocal estimation
__declspec(noinline) float_80_t Rcp(const float_80_t &);
// Square root
__declspec(noinline) float_80_t Sqrt(const float_80_t &);
// Trigonometric
__declspec(noinline) float_80_t Sin(const float_80_t &);
__declspec(noinline) float_80_t Cos(const float_80_t &);
// Logarithmic
__declspec(noinline) float_80_t Ln(const float_80_t &);
__declspec(noinline) float_80_t Log2(const float_80_t &);
__declspec(noinline) float_80_t Log10(const float_80_t &);

#endif // _62BC6D80_639F_42AC_A4E3_BDC7085266CC
