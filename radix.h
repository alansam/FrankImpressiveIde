
#pragma once
#ifndef radix_h
#define radix_h

#ifdef __cplusplus
#include <cstdio>
#include <cstdlib>
#include <cmath>
#else
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#endif
#include <unistd.h>

#ifdef __cplusplus
extern "C"
#endif
void RadixSortA(size_t len, int sort_this[len]);

#ifdef __cplusplus
extern "C"
#endif
void RadixSortD(size_t len, int sort_this[len]);

#ifdef __cplusplus
extern "C"
#endif
void RadixSort(size_t len, int sort_this[len], char dir);

//  Array Printer
inline
static void show_n_tell(size_t const len, int const ary[len],
                        size_t const bk) {
  for (size_t y_ = 0, c_ = 0; y_ < len; ++y_) {
    printf("%5d%s", ary[y_], (++c_ % bk == 0 ? "\n" : ""));
  }
  putchar('\n');
}

inline
static int smallest(size_t len, int search[len]) {
  int min = 0;
  for (size_t i_ = 0; i_ < len; ++i_) {
    min = min > search[i_] ? search[i_] : min;
  }
  return min;
}

inline
static void min_adjust(size_t len, int update[len], int min) {
  for (size_t i_ = 0; i_ < len; ++i_) {
    update[i_] -= min;
  }
}

#endif  /* radix_h */
