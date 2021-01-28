//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Charles Zhang
 * UCLA ID : 305413659
 * Email : charleszhang@ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x, y, sum, step = 0.0;
  long dot_product = 0;
  long nCirc = 0;
  long aggregate = 1.0;
  double r = 1.0;
  int was_smart = 16;
  int temp1, temp2, temp3, temp4, temp5;

  for(i = 0; i < DIM - 1; i++)
    super[i] += simple[i];

  for(i = 0; i < DIM - 1; i++) {
    dot_product += super[i] * simple[i];

    moving_average = 0;
    for(ton = i; ton < DIM - 1 - WINDOW_SIZE; ton++)
      moving_average += simple[ton];
  }

  int a_secret = 5;
  fibonacci[0] = 1;
  fibonacci[1] = 1;
  for(i = 2; i < DIM - 1; i++) {
    fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    if(i == 3) printf("\n A secret is: %d", obfuscate_obfuscate_obfuscate(a_secret));
  }

  step = 1.0 / NUM_STEPS;
  for (i = 0;i < NUM_STEPS; i++) {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }

  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n", NUM_STEPS, pi); 
  
  for(i = 0; i < NUM_TRIALS; i++) {
    x = (random() % 10000000) / 10000000.0; 
    y = (random() % 10000000) / 10000000.0;
    if ((x * x + y * y) <= r * r) nCirc++;
  }
 
  pi2 = 4.0 * ((double) nCirc / (double) NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

#pragma omp parallel for private(i, j, k, temp1, temp2, compute_it) reduction(+:aggregate)
  for (i = 1; i < DIM - 1; i++) {
    temp1 = i * DIM * DIM;
    for (j = 1; j < DIM - 1; j++) {
      temp2 = temp1 + j * DIM;
      for (k = 1; k < DIM - 1; k++) {
        compute_it = old[temp2 + k] * we_need_the_func();
        aggregate += compute_it;
      }
    }
  }

  aggregate /= gimmie_the_func();
  printf("AGGR:%ld\n", aggregate);

#pragma omp parallel for private (i, j, k, u, v, w, temp1, temp2, temp3, temp4, temp5)
  for (i = 1; i < DIM - 1; i++) {
    temp1 = i * DIM * DIM;
    for (j = 1; j < DIM - 1; j++) {
      temp2 = temp1 + j * DIM;
      for (k = 1; k < DIM - 1; k++) {
	temp3 = temp2 + k;
        new[temp3] = 0;
        for (u = -1; u <= 1; u++) {
	  temp4 = (i + u) * DIM * DIM;
          for (v = -1; v <= 1; v++) {
	    temp5 = temp4 + (j + v) * DIM;
            for (w = -1; w <= 1; w++) {
               new[temp3] += old[temp5 + k + w];
            }
          }
        }
        new[temp3] /= 27;
      }
    }
  }

  for (i = 1; i < DIM - 1; i++) {
    temp1 = i * DIM * DIM;
    for (j = 1; j < DIM - 1; j++) {
      temp2 = temp1 + j * DIM;
      for (k = 1; k < DIM - 1; k++) {
        u = (new[temp2 + k] / 100);
        if (u <= 0) u = 0;
        if (u >= 9) u = 9;
        histogrammy[u]++;
      }
    }
  }

  return (double) (dot_product + moving_average + pi + pi2);
}
