#include "balance_internal.h"
#include <tgmath.h>

const double a = 0.;
const double b = 1.;
const double F_AB = 2. / 3.;

void
f (double *p, size_t n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      p[i] = sqrt (p[i]);
    }
}

int
main (int argc, char *argv[])
{
  double tmp;

  _bal_adaptive_lobatto adaptlob = _bal_adaptive_lobatto_init (40);
  if (!adaptlob)
    abort ();

  tmp = _bal_adaptive_lobatto_integrate (f, 0., 1., adaptlob, 1e-16);

  if (fabs (tmp - F_AB) > 1e-6)
    abort ();

  _bal_adaptive_lobatto_destroy (adaptlob);
  return 0;
}
