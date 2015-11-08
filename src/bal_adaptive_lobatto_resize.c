#include "balance_internal.h"

void
_bal_adaptive_lobatto_resize (_bal_adaptive_lobatto in, size_t levels)
{
  double *tmp;
  size_t old_levels, old_n, n;

  if (!in)
    return;

  n = 12 * levels * (levels - 1) / 2;
  if (in->len < n)
    {
      tmp = 0;
      if (in->data)
	{
	  tmp = in->data;
	}

      old_n = in->len;
      in->len = n;
      in->data = (double *) malloc ((sizeof (double)) * n);

      if (!in->data)
	{
	  in->len = old_n;
	  in->data = tmp;
	  return;
	}

      if (tmp)
	{
	  memcpy ((void *) in->data, (void *) tmp, sizeof (double) * old_n);
	  free (tmp);
	}
    }
}
