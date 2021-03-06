#include "balance_internal.h"
#include <tgmath.h>

const double a = 0.;
const double b = 1.;
double F_AB = asin (1.);

void
f (double *p, size_t n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      p[i] = sqrt (1. / (1. - p[i] * p[i]));
      if (isinf (p[i]) | isnan (p[i]))
	{
	  p[i] = 0.;
	}
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
