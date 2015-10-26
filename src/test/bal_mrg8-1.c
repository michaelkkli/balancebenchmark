#include "balance_internal.h"

int
main (int argc, char *argv[])
{
  uint64_t buf[18];

  _bal_mrg8 (buf, 0);
  _bal_mrg8 (buf, 1);
  _bal_mrg8 (buf, 7);
  _bal_mrg8 (buf, 8);
  _bal_mrg8 (buf, 9);
  _bal_mrg8 (buf, 15);
  _bal_mrg8 (buf, 16);
  _bal_mrg8 (buf, 17);

  return 0;
}
