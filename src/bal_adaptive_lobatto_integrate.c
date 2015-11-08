/* 
 * Non-recursive adaptive Lobatto using four-point Gauss-Lobatto quadrature
 * and two successive Kronrod extensions following
 * Walter Gander and Walter Gautschi. "Adaptive Quadrature--Revisited".
 * BIT Numerical Mathematics, 84-101, 2000.
 * http://dx.doi.org/10.1023/A:1022318402393
 */
#include "balance_internal.h"
#include <float.h>
#include <tgmath.h>

double
_bal_adaptive_lobatto_integrate (void (*f) (double *, size_t),
				 double a,
				 double b,
				 _bal_adaptive_lobatto adaptlob, double tol)
{
  const double alpha = sqrt (2. / 3.);
  const double beta = sqrt (1. / 5.);
  const double x1 = .94288241569547971905635175843185720232;
  const double x2 = .64185334234578130578123554132903188354;
  const double x3 = .23638319966214988028222377349205292599;
  const double A = .015827191973480183087169986733305510591;
  const double B = .094273840218850045531282505077108171960;
  const double C = .15507198733658539625363597980210298680;
  const double D = .18882157396018245442000533937297167125;
  const double E = .19977340522685852679206802206648840246;
  const double F = .22492646533333952701601768799639508076;
  const double G = .24261107190140773379964095790325635233;
  const double apb = alpha + beta, amb = alpha - beta;
  const double opa = 1. + alpha, oma = 1. - alpha;
  double fx[7];
  double is, i1, i2;
  double m, h;
  double hd2, erri2, R;
  volatile double dtmp;
  double Q;
  size_t last;

  m = 0.5 * (a + b);
  h = 0.5 * (b - a);

  fx[0] = m - x1 * h;
  fx[1] = m - x2 * h;
  fx[2] = m - x3 * h;
  fx[3] = m + x3 * h;
  fx[4] = m + x2 * h;
  fx[5] = m + x1 * h;
  f (fx, 6);

  /* Kronrod extension of i1 calculated in two parts. */
  is = B * (fx[0] + fx[5]) + D * (fx[1] + fx[4]) + F * (fx[2] + fx[3]);

  fx[0] = a;
  fx[1] = m - alpha * h;
  fx[2] = m - beta * h;
  fx[3] = m;
  fx[4] = m + beta * h;
  fx[5] = m + alpha * h;
  fx[6] = b;
  f (fx, 7);

  /* Kronrod extension of four-point Gauss-Lobatto. */
  i1 =
    (h / 1470.) * (77. * (fx[0] + fx[6]) + 432. * (fx[1] + fx[5]) +
		   625. * (fx[2] + fx[4]) + 672. * fx[3]);

  /* Four-point Gauss-Lobatto. */
  i2 = (h / 6.) * (fx[0] + fx[6] + 5. * (fx[2] + fx[4]));

  /* Complete second Kronrod extension. */
  is +=
    A * (fx[0] + fx[6]) + C * (fx[1] + fx[5]) + E * (fx[2] + fx[4]) +
    G * fx[3];
  is *= h;

  erri2 = fabs (i2 - is);

  if (tol < DBL_EPSILON)
    {
      tol = DBL_EPSILON;
    }

  if (0. != erri2)
    {
      R = fabs ((is - i1) / erri2);
      if (R > 0 & R < 1.)
	{
	  tol = tol / R;
	}
    }

  is *= tol / DBL_EPSILON;

  if (0. == is)
    {
      is = b - a;
    }

  dtmp = i1 - i2;

  if (is + dtmp == is | m - alpha * h <= a | b <= m + alpha * h)
    {
      return i1;
    }
  else
    {
      if (adaptlob->len < 6 * 2)
	{
	  _bal_adaptive_lobatto_resize (adaptlob, 12 * 40 * 41 / 2);
	}

      hd2 = h / 2.;

      adaptlob->data[0] = m - opa * hd2;
      adaptlob->data[1] = oma * hd2;
      adaptlob->data[2] = m - apb * hd2;
      adaptlob->data[3] = amb * hd2;
      adaptlob->data[4] = m - beta * hd2;
      adaptlob->data[5] = beta * hd2;
      adaptlob->data[6] = m + beta * hd2;
      adaptlob->data[7] = beta * hd2;
      adaptlob->data[8] = m + apb * hd2;
      adaptlob->data[9] = amb * hd2;
      adaptlob->data[10] = m + opa * hd2;
      adaptlob->data[11] = oma * hd2;
      last = 12;
    }

  Q = 0.;

  do
    {
      if (last >= 2)
	{
	  last -= 2;
	}
      else
	{
	  last = 0;
	}
      m = adaptlob->data[last];
      h = adaptlob->data[last + 1];

      fx[0] = m - h;
      fx[1] = m - alpha * h;
      fx[2] = m - beta * h;
      fx[3] = m;
      fx[4] = m + beta * h;
      fx[5] = m + alpha * h;
      fx[6] = m + h;
      f (fx, 7);

      /* Kronrod extension of four-point Gauss-Lobatto. */
      i1 =
	(h / 1470.) * (77. * (fx[0] + fx[6]) + 432. * (fx[1] + fx[5]) +
		       625. * (fx[2] + fx[4]) + 672. * fx[3]);

      /* Four-point Gauss-Lobatto. */
      i2 = (h / 6.) * (fx[0] + fx[6] + 5. * (fx[2] + fx[4]));

      dtmp = i1 - i2;
      if (is + dtmp == is | m - alpha * h <= m - h | m + h <= m + alpha * h)
	{
	  Q += i1;
	}
      else
	{
	  if (adaptlob->len < last + 6 * 2)
	    {
	      _bal_adaptive_lobatto_resize (adaptlob, 2 * adaptlob->len);
	    }

	  hd2 = h / 2.;

	  adaptlob->data[last] = m - opa * hd2;
	  adaptlob->data[last + 1] = oma * hd2;
	  adaptlob->data[last + 2] = m - apb * hd2;
	  adaptlob->data[last + 3] = amb * hd2;
	  adaptlob->data[last + 4] = m - beta * hd2;
	  adaptlob->data[last + 5] = beta * hd2;
	  adaptlob->data[last + 6] = m + beta * hd2;
	  adaptlob->data[last + 7] = beta * hd2;
	  adaptlob->data[last + 8] = m + apb * hd2;
	  adaptlob->data[last + 9] = amb * hd2;
	  adaptlob->data[last + 10] = m + opa * hd2;
	  adaptlob->data[last + 11] = oma * hd2;
	  last += 12;
	}
    }
  while (0 != last);

  return Q;
}
