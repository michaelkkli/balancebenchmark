#include "balance_internal.h"

#include <stdlib.h>

_bal_andersen_qe_param
_bal_andersen_qe_param_init (
    double epsilon,
    double kappa,
    double rho,
    double theta,
    double V0,
    double X0,
    double delta_t,
    long long num_steps,
    long long path_block_size,
    long long num_path_blocks)
{
  _bal_andersen_qe_param param = (typeof(param))malloc (sizeof(_bal_andersen_qe_param_internal));
  if (!param) return;

  param->epsilon = epsilon;
  param->kappa = kappa;
  param->rho = rho;
  param->theta = theta;
  param->V0 = V0;
  param->X0 = X0;
  param->delta_t = delta_t;
  param->num_steps = num_steps;
  param->path_block_size = path_block_size;
  param->num_path_blocks = num_path_blocks;
  return param;
}

void
_bal_andersen_qe_param_destroy (_bal_andersen_qe_param param )
{
  free(param);
}
