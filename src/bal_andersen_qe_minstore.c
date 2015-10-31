#include "balance_internal.h"

#include <tgmath.h>

struct _bal_andersen_qe_minstore_timestep {
  double V;
  double lnX;
};
typedef struct _bal_andersen_qe_minstore_timestep timestep;

void _bal_andersen_qe_minstore (double *S, _bal_andersen_qe_random_variates rv,
                                _bal_andersen_qe_param param)
{
  size_t b,i,t, Sindex;
  timestep *tmp_ts;
  timestep tA, tB, *tnow, *tprev;

  double expmkd, one_m_expmkd;
  const double phi_c = 1.5;
  double m, s2, s2A, s2B, phi, two_phi_m1;
  double b2, a;
  double p, beta, u;

  double K0, K1, K2, K3, K4;
  const double gamma1 = .5, gamma2 = .5; /* Central: .5, .5. Euler: 1., 0. */

  expmkd = exp (-param->kappa*param->delta_t);
  one_m_expmkd = 1. - expmkd;

  s2A = (param->epsilon*param->epsilon*expmkd/param->kappa)*one_m_expmkd;
  s2B = (param->theta*param->epsilon*param->epsilon/2./param->kappa)
    *one_m_expmkd*one_m_expmkd;

  K0 = -param->rho * param->kappa * param->theta * param->delta_t / param->epsilon;
  K1 = param->delta_t * ( param->kappa * param->rho / param->epsilon - .5 );
  K2 = K1;
  K1 *= gamma1;
  K2 *= gamma2;
  K1 -= param->rho/param->epsilon;
  K2 += param->rho/param->epsilon;
  K3 = param->delta_t * ( 1. - param->rho * param->rho );
  K4 = K3;
  K3 *= gamma1;
  K4 *= gamma2;

  for (b=0; b<param->num_path_blocks; b++)
    {
      for (i=0; i<param->path_block_size; i++)
	{
	  Sindex = param->path_block_size * b + i;
	  tnow = &tA; tprev = &tB;

	  tprev->V = param->V0;
	  tprev->lnX = log (param->X0);

	  for (t=0; t<param->num_steps; t++)
	    {
	      if ( t>0 )
		{
		  m = param->theta + (tprev->V - param->theta)*expmkd;
		}
	      else
		{ 
		  m = param->theta;
		}

	      s2 = tprev->V*s2A + s2B;
	      phi = s2/(m*m);

	      if (phi < phi_c)
		{
		  two_phi_m1 = 2*m*m/s2;
		  b2 = two_phi_m1 + sqrt (two_phi_m1)*sqrt (two_phi_m1 - 1);
		  a = m/b2; /* b2 because 1. not subtracted yet. */
		  b2 -= 1.;

		  tnow->V = sqrt (b2) + rv->Zv[ Sindex*param->num_steps + t ];
		  tnow->V *= a*tnow->V;
		}
	      else
		{
		  p = (phi-1.)/(phi+1.);
		  beta = (1.-p)/m;
		  u = rv->Uv[ Sindex*param->num_steps + t ];

		  if (u>p)
		    {
		      tnow->V = log( (1.-p)/(1.-u) ) / beta;
		    }
		  else
		    {
		      tnow->V = 0.;
		    }
		}

	      tnow->lnX = tprev->lnX + K0 + K1*tprev->V + K2*tnow->V
	      + sqrt( K3*tprev->V + K4*tnow->V ) * rv->Z[ Sindex*param->num_steps + t];

	      tmp_ts = tnow;
	      tnow = tprev;
	      tprev = tmp_ts;
	    }
	  S[ Sindex ] = exp (tprev->lnX);
	}
    }
}
