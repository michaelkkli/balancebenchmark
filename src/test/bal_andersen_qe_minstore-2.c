#include "balance_internal.h"

int
main (int argc, char *argv[])
{
  _bal_andersen_qe_param param;
  _bal_andersen_qe_random_variates rv;
  double *S;
  const double S0 = 100., K = S0;
  const size_t num_steps = 64;
  const double delta_t = .5 / num_steps;
  const size_t path_block_size = 1;
  const size_t num_path_blocks = 1000000;
  const size_t m = num_steps * path_block_size * num_path_blocks;
  const size_t num_paths = path_block_size * num_path_blocks;
  long double call_price;
  size_t i;

  /* Heston 1993. At-the-money call price is $2.81. */
  param = _bal_andersen_qe_param_init (.1,
				       2.,
				       .5,
				       .01,
				       .01,
				       S0,
				       delta_t,
				       num_steps,
				       path_block_size, num_path_blocks);

  if (!param)
    abort ();

  rv = _bal_andersen_qe_random_variates_init (param);
  if (!rv)
    abort ();

  S = (double *) malloc (sizeof (double) * m);
  if (!S)
    abort ();

  _bal_andersen_qe_minstore (S, rv, param);

  call_price = 0.;
  for (i = 0; i < num_paths; i++)
    {
      if (S[i] > K)
	{
	  call_price += S[i] - K;
	}
    }
  call_price /= num_paths;

  if (fabs (call_price - 2.81) > 0.01)
    abort ();

  free (S);

  _bal_andersen_qe_random_variates_destroy (rv);
  _bal_andersen_qe_param_destroy (param);
}
