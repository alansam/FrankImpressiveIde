
#include "radix.h"

//  MARK: - Example from StackOverflow
void RadixSortA(size_t len, int sort_this[len]) {
  int max = 0, exp = 1;
  int * work;

  work = malloc(len * sizeof(int));
  if (work == NULL) {
    exit(EXIT_FAILURE);
  }

  for (size_t i_ = 0; i_ < len; i_++) {
    if (sort_this[i_] > max) {
      max = sort_this[i_];
    }
  }

  while (max / exp > 0) {
    int bucket[10] = { 0, };
    for (size_t i_ = 0; i_ < len; i_++) {
      bucket[sort_this[i_] / exp % 10]++;
    }

    for (size_t i_ = 1; i_ < 10; i_++) {
      bucket[i_] += bucket[i_ - 1];
    }

    for (ssize_t y_ = len - 1; y_ >= 0; y_--) {
      work[--bucket[sort_this[y_] / exp % 10]] = sort_this[y_];
    }

    for (size_t i_ = 0; i_ < len; i_++) {
      sort_this[i_] = work[i_];
    }

    exp *= 10;
  }

  free(work);
}

void RadixSortD(size_t len, int sort_this[len]) {
  int max = 0, exp = 1;
  int * work;

  work = malloc(len * sizeof(int));
  if (work == NULL) {
    exit(EXIT_FAILURE);
  }

  for (size_t i_ = 0; i_ < len; i_++) {
    if (sort_this[i_] > max) {
      max = sort_this[i_];
    }
  }

  while (max / exp > 0) {
    int bucket[10] = { 0, };
    for (size_t i_ = 0; i_ < len; i_++) {
      bucket[9 - sort_this[i_] / exp % 10]++;  // changed this line
    }

    for (size_t i_ = 1; i_ < 10; i_++) {
      bucket[i_] += bucket[i_ - 1];
    }

    for (ssize_t y_ = len - 1; y_ >= 0; y_--) {
      work[--bucket[9 - sort_this[y_] / exp % 10]] = sort_this[y_]; // changed this line
    }

    for (size_t i_ = 0; i_ < len; i_++) {
      sort_this[i_] = work[i_];              // changed this line
    }

    exp *= 10;
  }

  free(work);
}

#define AS_DEBUG_ 1
#undef AS_DEBUG_
/*
 *  Radix sort: handles +ve & -ve integers
 *  in ascending & descending order.
 */
void RadixSort(size_t len, int sort_this[len], char dir) {
  int max = 0, exp = 1;
  int * work;
  int min;

  work =
#ifdef __cplusplus
  (int *)
#endif
  malloc(len * sizeof(int));
  if (work == NULL) {
    exit(EXIT_FAILURE);
  }

  // shunt values in array so all values are +ve
  min = smallest(len, sort_this);
  min_adjust(len, sort_this, min);
#ifdef AS_DEBUG_
  show_n_tell(len, sort_this, 8);
#endif

  for (size_t i_ = 0; i_ < len; i_++) {
    if (sort_this[i_] > max) {
      max = sort_this[i_];
    }
  }

  int adjust;
  switch (dir) {
  case 'D':
    adjust = 9;
    break;

  case 'A':
  default:
    adjust = 0;
    break;
  }

  while (max / exp > 0) {
    int bucket[10] = { 0, };
    for (size_t i_ = 0; i_ < len; i_++) {
      bucket[abs(adjust - sort_this[i_] / exp % 10)]++;  // changed this line
    }

    for (size_t i_ = 1; i_ < 10; i_++) {
      bucket[i_] += bucket[i_ - 1];
    }

    for (ssize_t y_ = len - 1; y_ >= 0; y_--) {
      work[--bucket[abs(adjust - sort_this[y_] / exp % 10)]] =
        sort_this[y_]; // changed this line
    }

    for (size_t i_ = 0; i_ < len; i_++) {
      sort_this[i_] = work[i_];              // changed this line
    }

    exp *= 10;
  }

#ifdef AS_DEBUG_
  show_n_tell(len, sort_this, 8);
#endif
  //  return array to original values
  min_adjust(len, sort_this, -min);

  free(work);
}
