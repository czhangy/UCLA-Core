/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <cpuid.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "./options.h"
#include "./output.h"
#include "./rand64-hw.h"
#include "./rand64-sw.h"

/* Description of the current CPU.  */
struct cpuid { unsigned eax, ebx, ecx, edx; };

/* Return information about the CPU.  See <http://wiki.osdev.org/CPUID>.  */
static struct cpuid
cpuid (unsigned int leaf, unsigned int subleaf)
{
  struct cpuid result;
  asm ("cpuid"
       : "=a" (result.eax), "=b" (result.ebx),
	 "=c" (result.ecx), "=d" (result.edx)
       : "a" (leaf), "c" (subleaf));
  return result;
}

/* Return true if the CPU supports the RDRAND instruction.  */
static _Bool
rdrand_supported (void)
{
  struct cpuid extended = cpuid (1, 0);
  return (extended.ecx & bit_RDRND) != 0;
}

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  long long nbytes;
  struct flagState container;
  container.input = 0, container.output = -1, container.path = NULL;
  struct drand48_data state;
  long int t = time(NULL);
  srand48_r(t, &state);
  nbytes = handleOptions(argc, argv, &container);
  /* If handleOptions ran into an error */
  if (nbytes == -1)
    return 1;
  
  /* If rdrand was called and the system can't use the hardware implementation */
  if (container.input == 1 && !rdrand_supported()) {
    fprintf(stderr, "rdrand failure\n");
    return 1;
  }
  
  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (char* path);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  if (rdrand_supported ())
    {
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
  else
    {
      initialize = software_rand64_init;
      rand64 = software_rand64;
      finalize = software_rand64_fini;
    }
  int wordsize = sizeof rand64();
  int output_errno = 0;
  char* path = "/dev/random";

  /* Take care of /F arg */
  if (container.path == NULL) {
    initialize(path);
  } else {
    initialize(*(container.path));
    free(*(container.path));
  }
  
  if (container.input == 2) {
    /* Take care of mrand48_r implementation */
    long int res;
    wordsize = sizeof res;
    do {
      if (container.output == -1) {
	mrand48_r(&state, &res);
	int outbytes = nbytes < wordsize ? nbytes : wordsize;
	if (!writebytes (res, outbytes))
	  {
	    output_errno = errno;
	    break;
	  }
	nbytes -= outbytes;
      } else {
	char* buf;
	int j;
	buf = malloc(container.output);
	for (j = 0; j < nbytes && j < container.output * 1000; j++) {
	  long int res;
	  mrand48_r(&state, &res);
	  while (j < nbytes && j < container.output * 1000 && res > 0) {
	    buf[j] = res;
	    res >>= 8;
	    j++;
	  }
	}
	nbytes -= container.output;
	free(buf);
      }
    }
    while (0 < nbytes);
  } else {
    do {
      if (container.output == -1) {
	unsigned long long x = rand64 ();
	int outbytes = nbytes < wordsize ? nbytes : wordsize;
	if (!writebytes (x, outbytes))
	  {
	    output_errno = errno;
	    break;
	  }
	nbytes -= outbytes;
      } else {
	char* buf;
	FILE* f;
	int num;
	num = nbytes > container.output * 1000 ? container.output * 1000 : nbytes;
	buf = malloc(num);
	if (container.path == NULL)
	  f = fopen("/dev/random", "r");
	else
	  f = fopen(*(container.path), "r");
	fread(buf, 1, num, f);
	write(1, buf, num);
	nbytes -= num;
	free(buf);
      }
    }
    while (0 < nbytes);
  }

  //  if (container.path != NULL)
  //free(*(container.path));
  
  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }
  finalize ();
  return !!output_errno;
}
