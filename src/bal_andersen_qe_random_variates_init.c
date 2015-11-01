#include "balance_internal.h"

#include <stdlib.h>

_bal_andersen_qe_random_variates
_bal_andersen_qe_random_variates_init (_bal_andersen_qe_param param)
{
  size_t m =
    param->num_path_blocks * param->path_block_size * param->num_steps;
  uint64_t *buf;

  _bal_andersen_qe_random_variates rv =
    (typeof (rv)) malloc (sizeof (_bal_andersen_qe_random_variates_internal));
  if (!rv)
    return;

  rv->rand = (typeof (rv->rand)) malloc (sizeof (double) * 3 * m);
  if (!rv->rand)
    {
      free (rv);
      rv = 0;
      return;
    }
  rv->Zv = &rv->rand[0];
  rv->Uv = &rv->rand[m];
  rv->Z = &rv->rand[2 * m];

  buf = (uint64_t *) malloc (sizeof (uint64_t) * 3 * m);
  if (!buf)
    {
      _bal_andersen_qe_random_variates_destroy (rv);
      return;
    }

  _bal_mrg8 (buf, 3 * m);
  _bal_mrg8_normalize (rv->rand, buf, 3 * m);
  _bal_pja_invnorm (rv->rand, m);
  _bal_pja_invnorm (&rv->rand[2 * m], m);

  free (buf);

  return rv;
}

void
_bal_andersen_qe_random_variates_destroy (_bal_andersen_qe_random_variates rv)
{
  rv->Zv = 0;
  rv->Uv = 0;
  rv->Z = 0;
  free (rv->rand);
  rv->rand = 0;
}
