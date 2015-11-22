#include <complex.h>
#include <tgmath.h>

void
_bal_heston_characteristic_lord2006 (double complex * u_inout, int num,
				     double kappa, double omega, double rho,
				     double tau, double theta, double f,
				     double V0)
{
  double complex u;
  double complex twoalphahat, beta, twogamma, D, G, A, Bv;
  double complex expmDtau, betamD;

  for (int i = 0; i < num; i++)
    {
      u = u_inout[i];

      twoalphahat = -u * (u + I);
      beta = (double complex) kappa - I * omega * rho * u;
      twogamma = (double complex) omega *omega;

      D = sqrt (beta * beta - twoalphahat * twogamma);
      betamD = beta - D;
      G = betamD / (beta + D);

      expmDtau = exp (-D * tau);
      Bv = betamD / twogamma * (1. - expmDtau) / (1. - G * expmDtau);

      A =
	(double complex) kappa *theta / twogamma * (betamD * tau -
						    2. *
						    log ((G * expmDtau -
							  1.) / (G - 1.)));

      u_inout[i] = exp (I * u * f + A + Bv * V0);
    }
}
