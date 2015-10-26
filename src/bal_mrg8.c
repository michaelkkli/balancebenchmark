#include "balance_internal.h"
#include <stdlib.h>
#include <string.h>

/* From https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Typeof.html */
#define _bal_max(a,b) \
  ({ typeof (a) _a = (a); \
   typeof (b) _b = (b); \
   _a > _b ? _a : _b; })
#define _bal_min(a,b) \
  ({ typeof (a) _a = (a); \
   typeof (b) _b = (b); \
   _a < _b ? _a : _b; })

void
_bal_mrg8 (uint64_t * ptr, size_t num)
{
  static uint64_t x[8];
  const uint64_t a[] = { 1089656042, 1906537547, 1764115693, 1304127872,
    189748160, 1984088114, 626062218, 1927846343
  };
  const uint64_t mask = (uint64_t) 0x7FFFFFFF;
  uint64_t s1, s2, s;
  double norm = 4.65661287525e-10;

  static int initialized = 0;
  size_t i, j, k, num_from_ptr;
  const uint64_t *a_split;
  uint64_t *s_split;

  if (!initialized)
    {
      x[0] = 97531ULL;
      x[1] = 4525455822575795487ULL >> 32;	// HP 50g calculated value.
      x[2] = 4344602724667842419ULL >> 32;	// HP 50g calculated value.
      x[3] = 6476166431153771575ULL >> 32;	// HP 50g calculated value.
      x[4] = 586183196364871339ULL >> 32;	// HP 50g calculated value.
      x[5] = 7505285344278696207ULL >> 32;	// HP 50g calculated value.
      x[6] = 3044147933607407779ULL >> 32;	// HP 50g calculated value.
      x[7] = 2916917746092927399ULL >> 32;	// HP 50g calculated value.
      initialized = 1;
    }

  for (i = 0; i < num; i++)
    {
      s1 = 0ULL;
      s2 = 0ULL;
      a_split = 0;

      /* Both x and ptr must be used to calculate the next random number
       * and num_from_ptr is the number of values to use from ptr.
       * This variable is perhaps the most important in this function. */
      num_from_ptr = _bal_min (i, 8);

      if (num_from_ptr >= 8)	/* s1 and s2 need contiguous access to ptr. */
	{
	  for (j = 0; j < 4; j++)
	    {
	      s1 += a[j] * x[i - 1 - j];
	    }
	  for (j = 4; j < 8; j++)
	    {
	      s2 += a[j] * x[i - 1 - j];
	    }
	  s = (s1 & mask) + (s1 >> 31) + (s2 & mask) + (s2 >> 31);
	  ptr[i] = (s & mask) + (s >> 31);
	  continue;
	}
      else if (num_from_ptr <= 4)	/* s2 needs contiguous access to x. */
	{

	  for (j = 4; j < 8; j++)
	    {
	      /* n=4, start from 0
	         n=3, start from 1 */
	      s2 += a[j] * x[j - num_from_ptr];
	    }

	  if (1 <= num_from_ptr & num_from_ptr <= 3)	/* s1 split */
	    {
	      a_split = &a[0];
	      s_split = &s1;
	    }
	  else if (0 == num_from_ptr)	/* s1 needs contiguous access to x */
	    {
	      for (j = 0; j < 4; j++)
		{
		  s1 += a[j] * x[j];
		}
	    }
	  else			/* s1 needs contiguous access to ptr. */
	    {
	      for (j = 0; j < 4; j++)
		{
		  s1 += a[j] * ptr[i - 1 - j];
		}
	    }
	}
      else			/* s1 contiguous access to ptr. s2 needs split access. */
	{
	  for (j = 0; j < 4; j++)
	    {
	      s1 += a[j] * ptr[i - 1 - j];
	    }
	  a_split = &a[4];
	  s_split = &s2;
	}

      if (a_split)
	{
	  /* Three distinct cases so easier to enumerate than to use loops
	   * due to forward access to a and x but backward access to ptr. */

	  if (1 == num_from_ptr | 5 == num_from_ptr)
	    {
	      *s_split += a_split[0] * ptr[0];
	      *s_split += a_split[1] * x[0];
	      *s_split += a_split[2] * x[1];
	      *s_split += a_split[3] * x[2];
	    }
	  else if (2 == num_from_ptr | 6 == num_from_ptr)
	    {
	      *s_split += a_split[0] * ptr[1];
	      *s_split += a_split[1] * ptr[0];
	      *s_split += a_split[2] * x[0];
	      *s_split += a_split[3] * x[1];
	    }
	  else			/* num_from_ptr is 3 or 7. */
	    {
	      *s_split += a_split[0] * ptr[2];
	      *s_split += a_split[1] * ptr[1];
	      *s_split += a_split[2] * ptr[0];
	      *s_split += a_split[3] * x[0];
	    }
	}

      s = (s1 & mask) + (s1 >> 31) + (s2 & mask) + (s2 >> 31);
      ptr[i] = (s & mask) + (s >> 31);
      continue;
    }

  /* Copy last eight into buffer. */
  if (num >= 8)
    {
      for (i = 0; i < 8; i++)
	{
	  x[i] = ptr[num - 1 - i];
	}
    }
  else				/* Split copy. */
    {
      for (i = 7; i > num - 1; i--)	/* Shuffle the x. */
	{
	  x[i] = x[i - num];
	}

      for (i = 0; i < num; i++)	/* Reverse access in ptr. */
	{
	  x[i] = ptr[num - i - 1];
	}
    }
}
