#include <immintrin.h>

/* Initialize the hardware rand64 implementation.  */
void
hardware_rand64_init (char* path)
{
}

/* Return a random value, using hardware operations.  */
unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

/* Finalize the hardware rand64 implementation.  */
void
hardware_rand64_fini (void)
{
}
