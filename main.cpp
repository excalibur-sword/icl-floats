#include "double_float_80.h"
#include <emmintrin.h>
#include <stdio.h> // printf

using f80 = float_80_t;
using df80 = double_float_80_t;

// Rump's example
template <typename T> T Rump(void) {
  T a = 77617.0;
  T b = 33096.0;
  T b2 = b*b;
  T b4 = b2*b2;
  T b6 = b4*b2;
  T b8 = b4*b4;
  T a2 = a*a;
  T firstExpr = 11*a2*b2 - b6 - 121*b4 - 2;
  return 333.75*b6 + a2*firstExpr + 5.5*b8 + (a/(2.0*b));
}

template <typename T> void PrintRump(void);
template <> void PrintRump<double>(void) {
  printf("Rump<double>:          %+1.9e\n", Rump<double>());
}
template <> void PrintRump<long double>(void) {
  printf("Rump<long double>:     %+1.9e\n", (double)Rump<long double>());
}
template <> void PrintRump<f80>(void) {
  printf("Rump<float_80>:        %+1.9e\n", Rump<f80>().ToDouble());
}
template <> void PrintRump<df80>(void) {
  printf("Rump<double_float_80>: %+1.9e\n", Rump<df80>().Hi().ToDouble());
}

int main(void) {
  // clear flush-to-zero, and
  // clear denormals-are-zero mode
  _mm_setcsr(_mm_getcsr() & 0x7fbfu);

  // masks all fpu exceptions,
  // sets rounding to nearest, and
  // sets the precision to double extended, and
  // sets affine infinity
  fpu_set_cw(0x133fu);

  PrintRump<double>();
  PrintRump<long double>(); // with compiler option /Qlong-double
  PrintRump<f80>();
  PrintRump<df80>();

  return 0;
}
