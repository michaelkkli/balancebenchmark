#include "balance_internal.h"
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  const size_t N = 10000000;
  uint64_t *buf;
  double *p;
  size_t i;
  long int count = 0;

  buf = (uint64_t*)malloc(N*sizeof(uint64_t));
  if ( !buf ) abort();

  p = (double*)malloc(N*sizeof(double));

  _bal_mrg8 (buf, N);

  for (i = 0; i < N; i++)
    {
      p[i] = (double) buf[i] / (uint64_t) 0x7FFFFFFF;
    }

  free(buf);

  _bal_pja_invnorm (p, N);

  for (i = 0; i < N; i++)
    {
      if (p[i] < .0)
	{
	  count++;
	}
    }

  free(p);

  if ( (double)count / N < 0.49 | 0.51 < (double)count / N )
    {
      abort ();
    }

  return 0;
}
