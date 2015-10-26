#include "balance_internal.h"
#include <assert.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  uint64_t mcg[8];
  const uint64_t a[] = { 1089656042, 1906537547, 1764115693, 1304127872,
    189748160, 1984088114, 626062218, 1927846343
  };
  uint64_t buf[1];
  uint64_t m = 6364136223846793005ULL;
  uint64_t s1 = 0ULL, s2 = 0ULL, s, mask = 0x7FFFFFFF;
  int i;

  mcg[0] = 97531ULL;

  for (i = 1; i < 8; i++)
    {
      mcg[i] = m * mcg[i - 1];
    }

  for (i = 1; i < 8; i++)
    {
      mcg[i] = mcg[i] >> 32;
    }

  if (mcg[1] != 4525455822575795487LL >> 32) // HP 50g calculated value.
    abort ();			
  if (mcg[2] != 4344602724667842419LL >> 32) // HP 50g calculated value.
    abort ();			
  if (mcg[3] != 6476166431153771575LL >> 32) // HP 50g calculated value.
    abort ();			
  if (mcg[4] != 586183196364871339LL >> 32) // HP 50g calculated value.
    abort ();			
  if (mcg[5] != 7505285344278696207LL >> 32) // HP 50g calculated value.
    abort ();			
  if (mcg[6] != 3044147933607407779LL >> 32) // HP 50g calculated value.
    abort ();			
  if (mcg[7] != 2916917746092927399LL >> 32) // HP 50g calculated value.
    abort ();			

  for (i = 0; i < 4; i++)
    {
      s1 += a[i] * mcg[i];
    }

  for (i = 4; i < 8; i++)
    {
      s2 += a[i] * mcg[i];
    }
  s = (s1 & mask) + (s1 >> 31) + (s2 & mask) + (s2 >> 31);
  s = (s & mask) + (s >> 31);

  buf[0] = 0ULL;
  _bal_mrg8 (buf, 1);

  assert (s == buf[0]);

  return 0;
}
