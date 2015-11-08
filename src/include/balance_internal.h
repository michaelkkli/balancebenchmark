#ifndef BALANCE_INTERNAL_H
#define BALANCE_INTERNAL_H
/* Guard macros placed before pragma once to allow multiple-include
 * optimization if pragma once is unsupported.
 * https://gcc.gnu.org/onlinedocs/cppinternals/Guard-Macros.html
 */
#pragma once

#include <stdint.h>
#include <stdlib.h>

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

typedef struct
{
  double *data;
  size_t len;
} _bal_adaptive_lobatto_internal, *_bal_adaptive_lobatto;

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

void
_bal_andersen_qe_random_variates_destroy (_bal_andersen_qe_random_variates);

void _bal_andersen_qe_minstore (double *S, _bal_andersen_qe_random_variates,
				_bal_andersen_qe_param);

_bal_adaptive_lobatto _bal_adaptive_lobatto_init (size_t levels);

void _bal_adaptive_lobatto_destroy (_bal_adaptive_lobatto);

void _bal_adaptive_lobatto_reize (_bal_adaptive_lobatto, size_t levels);

double
_bal_adaptive_lobatto_integrate (void (*f) (double *, size_t),
				 double a,
				 double b, _bal_adaptive_lobatto, double tol);

void _bal_mrg8 (uint64_t * out, size_t num);
void _bal_mrg8_normalize (double *out, uint64_t * in, size_t num);

void _bal_pja_invnorm (double *inout, size_t num);

#endif /* BALANCE_INTERNAL_H */
