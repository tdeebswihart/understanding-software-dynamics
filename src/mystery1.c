// Sample mystery program to measure how long an add takes. Flawed.
// Copyright 2021 Richard L. Sites

#include "instrumentation/instrumentation.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h> // time()

static const int kIterations = 1000 * 1000000;

int main(int argc, const char **argv) {
  uint64_t sum = 0;

  time_t t = time(NULL);       // A number that the compiler does not know
  volatile int incr = t & 255; // Unknown increment 0..255

  int rc = start_instrumentation();
  if (rc != 0) {
    return rc;
  }
  for (int i = 0; i < kIterations; ++i) {
    sum += incr;
  }
  stop_instrumentation();
  instrumentation_result res = get_instrumentation_result();
  printf("Cycles per iteration: %.2f\n\n", res.cycles / (double)kIterations);
  print_instrumentation_report();
  fprintf(stdout, "%lu %lu\n", t, sum); // Make sum live

  return 0;
}
