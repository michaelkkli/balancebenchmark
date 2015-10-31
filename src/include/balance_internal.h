#ifndef BALANCE_INTERNAL_H
#define BALANCE_INTERNAL_H
/* Guard macros placed before pragma once to allow multiple-include
 * optimization if pragma once is unsupported.
 * https://gcc.gnu.org/onlinedocs/cppinternals/Guard-Macros.html
 */
#pragma once

#include <stdint.h>
#include <string.h>

typedef struct
{
  double epsilon;
  double kappa;
  double rho;
  double theta;
  double V0;
  double X0;

  double delta_t;
  long long num_steps;

  long long path_block_size;
  long long num_path_blocks;
} _bal_andersen_qe_param_internal, *_bal_andersen_qe_param;

typedef struct
{
  double *Zv;
  double *Uv;
  double *Z;
  double *rand;
} _bal_andersen_qe_random_variates_internal,
  *_bal_andersen_qe_random_variates;

_bal_andersen_qe_param
_bal_andersen_qe_param_init (double epsilon,
			     double kappa,
			     double rho,
			     double theta,
			     double V0,
			     double X0,
			     double delta_t,
			     long long num_steps,
			     long long path_block_size,
			     long long num_path_blocks);
void _bal_andersen_qe_param_destroy (_bal_andersen_qe_param);

_bal_andersen_qe_random_variates
_bal_andersen_qe_random_variates_init (_bal_andersen_qe_param);

void _bal_andersen_qe_random_variates_destroy (_bal_andersen_qe_random_variates);

void _bal_andersen_qe_minstore (double *St, _bal_andersen_qe_random_variates,
				_bal_andersen_qe_param);

void _bal_mrg8 (uint64_t * ptr, size_t num);
void _bal_mrg8_normalize (double * ptr, uint64_t *i, size_t num);

void _bal_pja_invnorm (double *p, size_t num);

#endif /* BALANCE_INTERNAL_H */
