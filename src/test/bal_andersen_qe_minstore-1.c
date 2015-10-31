#include "balance_internal.h"

int
main (int argc, char *argv[])
{
  _bal_andersen_qe_param param;
  _bal_andersen_qe_random_variates rv;

  /* Heston 1993. At-the-money call price is $2.83. */
  param = _bal_andersen_qe_param_init (
    .1,
    2.,
    -.5,
    .01,
    .01,
    100.,
    1./32,
    16,
    1,
    1000000);
  if(!param) abort();

  rv = _bal_andersen_qe_random_variates_init(param);
  if(!rv) abort();

  _bal_andersen_qe_random_variates_destroy(rv);
  _bal_andersen_qe_param_destroy(param);
}
