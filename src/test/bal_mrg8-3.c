#include "balance_internal.h"
#include <stdlib.h>
#include <stdint.h>

int
main (int argc, char *argv[])
{
  uint64_t mcg[9];
  uint64_t m = 6364136223846793005ULL;
  const uint64_t a[] = { 1089656042, 1906537547, 1764115693, 1304127872,
    189748160, 1984088114, 626062218, 1927846343
  };
  uint64_t x[8];
  const int N = 20;
  uint64_t buf[N], buf2[N];
  uint64_t s1, s2, s;
  const uint64_t mask = 0x7FFFFFFF;
  size_t i,j;

  mcg[0] = 97531ULL; /* Seed. */

  for (i = 1; i < 9; i++)
    {
      mcg[i] = m * mcg[i - 1];
    }

  for (i = 0; i < 8; i++)
    {
      x[i] = mcg[i+1] >> 32; /* i+1 to omit the seed. */
    }

  /* Based on K. Miura's mrg8.f. */
  for (i = 0; i < N; i++)
    {
      s1 = 0ULL; s2 = 0ULL;
      for (j = 0; j < 4; j++)
	{
	  s1 += a[j] * x[j];
	}

      for (j = 4; j < 8; j++)
	{
	  s2 += a[j] * x[j];
	}
      s = (s1 & mask) + (s1 >> 31) + (s2 & mask) + (s2 >> 31);
      s = (s & mask) + (s >> 31);
      buf[i] = s;

      for (j=7; j>0; j--)
	{
	  x[j] = x[j-1];
	}
      x[0] = s;
    }

    _bal_mrg8 (buf2, N);

    for (i=0; i<N; i++)
      {
	if ( buf[i] != buf2[i] )
	  abort();
      }

    return 0;
}
