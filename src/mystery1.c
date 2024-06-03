// Sample mystery program to measure how long an add takes. Flawed.
// Copyright 2021 Richard L. Sites

#include "instrumentation/instrumentation.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define xstr(a) str(a)
#define str(a) #a

// Yes I know: the formatting arg for fprintf is wrong. It doesn't matter: all
// we need is for sum to be marked as live by the compiler.
#define measure(T, op)                                                         \
  ({                                                                           \
    time_t t = time(NULL);                                                     \
    volatile int64_t incr = t & 255;                                           \
    int rc = start_instrumentation();                                          \
    if (rc != 0) {                                                             \
      return rc;                                                               \
    }                                                                          \
    T sum = 12;                                                                \
    for (int i = 0; i < kIterations; ++i) {                                    \
      sum op incr;                                                             \
    }                                                                          \
    stop_instrumentation();                                                    \
    instrumentation_result res = get_instrumentation_result();                 \
    printf("Cycles per iteration for " xstr(T) " " xstr(op) ": %.2f\n\n",      \
           res.cycles / (double)kIterations);                                  \
    fprintf(stdout, "%lu %llu\n", t, sum);                                     \
  })

static const int kIterations = 100000000;

int main(int argc, const char **argv) {
  measure(int64_t, +=);
  measure(int64_t, *=);
  measure(int64_t, /=);
  measure(double, +=);
  measure(double, *=);
  measure(double, /=);
  return 0;
}
