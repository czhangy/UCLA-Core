#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "options.h"

int
handleOptions (int argc, char **argv, struct flagState* container)
{
  /* Check arguments.  */
  char c;
  bool iFlag = false, oFlag = false, valid = true;
  char iOpt[] = "rdrand", oOpt[] = "stdio";
  while ((c = getopt(argc, argv, ":i:o:")) != -1) {
    switch(c) {
    case 'i':
      iFlag = true;
      if (optarg[0] == '-') // if following "argument" is actually a flag
	optind -= 1;
      else if (optarg[0] == 'o') { // if following arg is a joint flag
	optind -= 1; // reprocess o flag
	strcpy(argv[optind], "-o"); // i is guaranteed to have a default arg
      }
      else if (optind != argc)// get arg
	strcpy(iOpt, optarg);
      else // picked up last value as arg, revert
	optind--;
      break;
    case 'o':
      oFlag = true;
      if (optarg[0] == '-') // check if following "argument" is actually a flag
	optind -= 1;
      else if (optarg[0] == 'i') { // if following arg is a joint flag
	optind -= 1;
	strcpy(argv[optind], "-i");
      }
      else if (optind != argc) // get arg
	strcpy(oOpt, optarg);
      else // picked up last value as arg, revert
	optind--;
      break;
    case '?': // unknown flag passed, error out
      valid = false;
      break;
    case ':':
      if (strcmp(argv[optind - 1], "-i") == 0) // adjust for flags begin called with no args
	iFlag = true;
      else
	oFlag = true;    
    }
  }
  long long nbytes;
  nbytes = -2; // should never be returned
  if (optind >= argc) // missing nbytes
    valid = false;
  else {
    char *endptr;
    errno = 0;
    nbytes = strtoll(argv[optind], &endptr, 10);
    if (errno) // failed conversion
	perror(argv[optind]);
    else // check if pure number
	valid = !*endptr;
  }
  if (iFlag) { // check -i arg
    if (strcmp(iOpt, "rdrand") == 0)
      container->input = 1;
    else if (strcmp(iOpt, "mrand48_r") == 0)
      container->input = 2;
    else if (iOpt[0] == '/') {
      char* var;
      var = (char*)malloc(strlen(iOpt) + 1);
      strcpy(var, iOpt);
      container->input = 3;
      container->path = &var;
    }
    else
      valid = false;
  }

  if (oFlag) { // check -o arg
    if (strcmp(oOpt, "stdio")) { // ignore if stdio
      int len, i;
      len = strlen(oOpt);
      for (i = 0; i < len; i++) // check if string is a number, overflow ignored
	if (!isdigit(oOpt[i]))
	  break;
      if (len == i)
	container->output = atoi(oOpt);
      else // string contains non-numeric char
	valid = false;
    }
  }     
  
  if (!valid) // fail condition
  {
    fprintf(stderr, "Usage: %s [-i input] [-o output] nbytes\n", argv[0]);
    return -1;
  }
  return nbytes;
}


