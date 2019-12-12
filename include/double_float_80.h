#ifndef _B1F5CAB2_411B_47CA_9432_829207681B13
#define _B1F5CAB2_411B_47CA_9432_829207681B13

#include "float_80.h"

class double_float_80_t {
  float_80_t x[2];

  inline __declspec(nothrow) double_float_80_t(
    const float_80_t &hi, const float_80_t &lo
  ) {
    this->x[0] = hi;
    this->x[1] = lo;
  }
public:
  inline __declspec(nothrow) ~double_float_80_t(void) = default;
  inline __declspec(nothrow) double_float_80_t(void) {}
  inline __declspec(nothrow) double_float_80_t(const float_80_t &ld) {
    this->x[0] = ld;
    this->x[1] = {0};
  }
  inline __declspec(nothrow) double_float_80_t(const double_float_80_t &) = default;

  inline __declspec(nothrow) float_80_t Hi(void) const {return this->x[0];}
  inline __declspec(nothrow) float_80_t Lo(void) const {return this->x[1];}

  // Assignments
  inline double_float_80_t & operator =(const double &rh) {
    __asm {
      mov rdx, rh
      mov rcx, this
      fld qword ptr [rdx]
      fstp tbyte ptr [rcx + 0*10]
      fldz
      fstp tbyte ptr [rcx + 1*10]
    }
  }
  double_float_80_t & operator =(const double_float_80_t &) = default;

  // Unary Minus
  inline __declspec(nothrow) double_float_80_t operator -(void) const {
    return {-this->x[0], -this->x[1]};
  }
  inline bool IsZero(void) const {return this->x[0].IsZero() && this->x[1].IsZero();}

  // Self-Additions
  double_float_80_t & operator +=(const float_80_t &);
  double_float_80_t & operator +=(const double_float_80_t &);

  // Self-Subtractions
  double_float_80_t & operator -=(const float_80_t &);
  double_float_80_t & operator -=(const double_float_80_t &);

  // Self-Multiplications
  double_float_80_t & operator *=(const float_80_t &);
  double_float_80_t & operator *=(const double_float_80_t &);

  // Self-Divisions
  double_float_80_t & operator /=(const float_80_t &);
  double_float_80_t & operator /=(const double_float_80_t &);
};

// Additions
inline double_float_80_t operator +(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t += b;
  return t;
}
inline double_float_80_t operator +(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(b);
  t += a;
  return t;
}
inline double_float_80_t operator +(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t += b;
  return t;
}

// Subtractions
inline double_float_80_t operator -(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t -= b;
  return t;
}
inline double_float_80_t operator -(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t -= b;
  return t;
}
inline double_float_80_t operator -(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t -= b;
  return t;
}

// Multiplications
inline double_float_80_t operator *(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t *= b;
  return t;
}
inline double_float_80_t operator *(
  const float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(b);
  t *= a;
  return t;
}
inline double_float_80_t operator *(
  const double_float_80_t &a, const double_float_80_t &b
) {
  double_float_80_t t(a);
  t *= b;
  return t;
}

// Divisions
inline double_float_80_t operator /(
  const double_float_80_t &a, const float_80_t &b
) {
  double_float_80_t t(a);
  t /= b;
  return t;
}
inline double_float_80_t operator /(
  const float_80_t &a, const double_float_80_t& b
) {
  double_float_80_t t(a);
  t /= b;
  return t;
}
inline double_float_80_t operator /(
  const double_float_80_t &a, const double_float_80_t& b
) {
  double_float_80_t t(a);
  t /= b;
  return t;
}

#endif // _B1F5CAB2_411B_47CA_9432_829207681B13
