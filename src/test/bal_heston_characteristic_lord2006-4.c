#include "balance_internal.h"
#define _USE_MATH_DEFINES
#include <stdbool.h>
#include <tgmath.h>

const double a = 0.;
const double b = 1.;
const double F_AB = 2.81;

const double S = 100.;
const double F = 100.;
const double V0 = .01;
const double theta = .01;
const double kappa = 2.;
const double omega = .1;
const double rho = .5;
const double tau = .5;
const double K = 100.;
double k;
const double alpha = 13.9375;

bool cbuf_initialized = false;
double complex *cbuf;
size_t cbuf_len = 0;

double complex ctmp;
double psizero;
double complex ialpha;
double complex ialphap1;
double Cinf;

void
f (double *v, size_t n)
{
  const double complex mik = -I * k;
  double vtmp;
  double tinf = -rho * (kappa * theta * tau + V0) / omega + log (F / K);
  double scaledv;

  if (!cbuf_initialized)
    {
      cbuf = (double complex *) malloc (sizeof (double complex) * n);
      if (!cbuf)
	{
	  abort ();
	}
      else
	{
	  cbuf_len = n;
	}
      cbuf_initialized = true;
    }
  else
    {
      if (cbuf_len < n)
	{
	  cbuf_len = 2 * cbuf_len > n ? 2 * cbuf_len : n;
	  free (cbuf);
	  cbuf =
	    (double complex *) malloc (sizeof (double complex) * cbuf_len);
	  if (!cbuf)
	    {
	      abort ();
	    }
	}
    }

  for (size_t i = 0; i < n; i++)
    {
      cbuf[i] = -log (v[i]) / Cinf - ialphap1;
    }

  _bal_heston_characteristic_lord2006 (cbuf, n, kappa, omega, rho, tau, theta,
				       log (F), V0);

  for (size_t i = 0; i < n; i++)
    {
      scaledv = -log (v[i]) / Cinf;
      ctmp =
	-exp (scaledv * mik) * cbuf[i] / (v[i] - ialpha) / (v[i] - ialphap1);
      vtmp = creal (ctmp) / v[i];
      if (isfinite (vtmp) & isfinite (cimag (ctmp)))
	{
	  v[i] = vtmp;
	}
      else
	{
	  if (isfinite (scaledv) & isfinite (scaledv))
	    {
	      vtmp =
		-psizero * exp (-scaledv * Cinf) * cos (scaledv * tinf) /
		scaledv / scaledv / v[i];
	      if (isfinite (vtmp))
		{
		  v[i] = vtmp;
		}
	      else
		{
		  v[i] = 0.;
		}
	    }
	  else
	    {
	      v[i] = 0.;
	    }
	}
    }
}

int
main (int argc, char *argv[])
{
  double tmp;
  k = log (K);
  ialpha = I * alpha;
  ialphap1 = I * (alpha + 1.);
  Cinf = sqrt (1. - rho * rho) * (V0 + kappa * theta * tau) / omega;

  ctmp = -ialphap1;
  _bal_heston_characteristic_lord2006 (&ctmp, 1, kappa, omega, rho, tau,
				       theta, log (F), V0);
  ctmp /= alpha * (alpha + 1.);
  psizero = creal (ctmp);

  _bal_adaptive_lobatto adaptlob = _bal_adaptive_lobatto_init (40);
  if (!adaptlob)
    abort ();

  tmp = _bal_adaptive_lobatto_integrate (f, a, b, adaptlob, 1e-16);
  tmp *= exp (-alpha * k) / M_PI / Cinf;

  if (!isfinite (tmp) | fabs (tmp - F_AB) > .001 * F_AB)
    abort ();

  _bal_adaptive_lobatto_destroy (adaptlob);
  free (cbuf);
  return 0;
}
