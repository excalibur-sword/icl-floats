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

static const int n_inv_fact = 15;
static const double inv_fact[n_inv_fact][2] = {
  { 1.66666666666666657e-01,  9.25185853854297066e-18},
  { 4.16666666666666644e-02,  2.31296463463574266e-18},
  { 8.33333333333333322e-03,  1.15648231731787138e-19},
  { 1.38888888888888894e-03, -5.30054395437357706e-20},
  { 1.98412698412698413e-04,  1.72095582934207053e-22},
  { 2.48015873015873016e-05,  2.15119478667758816e-23},
  { 2.75573192239858925e-06, -1.85839327404647208e-22},
  { 2.75573192239858883e-07,  2.37677146222502973e-23},
  { 2.50521083854417202e-08, -1.44881407093591197e-24},
  { 2.08767569878681002e-09, -1.20734505911325997e-25},
  { 1.60590438368216133e-10,  1.25852945887520981e-26},
  { 1.14707455977297245e-11,  2.06555127528307454e-28},
  { 7.64716373181981641e-13,  7.03872877733453001e-30},
  { 4.77947733238738525e-14,  4.39920548583408126e-31},
  { 2.81145725434552060e-15,  1.65088427308614326e-31}
};

// Computes sin(a) using Taylor series. Assumes |a| <= pi/32.
df80 SinTaylor(const df80 &a) {
  if (a.IsZero()) return a;

  df80 x = -a*a;
  df80 s = a;
  df80 r = a;
  df80 t;

  f80 thresh = 0.5*Abs(a.Hi())*F80_EPS;
  int i = 0;
  do {
    r *= x;
    t = r*inv_fact[i][0];
    s += t;
    i += 2;
    printf("%2d = %+1.14e %+1.14e\n", i, s.Hi().ToDouble(), s.Lo().ToDouble());
  } while (i < n_inv_fact && Abs(t.Hi()) > thresh);

  return s;
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

  printf("\nsinus using Taylor series\n");
  SinTaylor(F80_PI/64);

  return 0;
}
