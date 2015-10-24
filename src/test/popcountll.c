#include <stdint.h>

int
main (int argc, char *argv[])
{
  uint64_t a[] = { 0, 1, (uint64_t) 1 << 63, 0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF };
  int b[] = { 0, 1, 1, 32, 64 };

  int n = sizeof (a) / sizeof (a[0]);

  for (int i = 0; i < n; i++)
    {
      if (__builtin_popcountll (a[i]) != b[i])
	{
	  return 1;
	}
    }
  return 0;
}
