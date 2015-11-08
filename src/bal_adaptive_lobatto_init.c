#include "balance_internal.h"

_bal_adaptive_lobatto
_bal_adaptive_lobatto_init (size_t levels)
{
  _bal_adaptive_lobatto tmp =
    (_bal_adaptive_lobatto) malloc (sizeof (_bal_adaptive_lobatto_internal));
  if (!tmp)
    return 0;

  tmp->data = 0;
  tmp->len = 0;

  _bal_adaptive_lobatto_resize (tmp, levels);
  if (!tmp->data)
    {
      free (tmp);
      return 0;
    }

  return tmp;
}

void
_bal_adaptive_lobatto_destroy (_bal_adaptive_lobatto in)
{
  free (in);
}
