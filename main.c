//  @see: https://rosettacode.org/wiki/Sorting_algorithms/Radix_sort#C
//  @see: https://stackoverflow.com/questions/33657031/radix-sort-descending
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

void RadixSortA(size_t len, int sort_this[len]);
void RadixSortD(size_t len, int sort_this[len]);
void RadixSort(size_t len, int sort_this[len], char dir);

//  Array Printer
inline
static void show_n_tell(size_t const len, int const ary[len],
                        size_t const bk) {
  for (size_t y_ = 0, c_ = 0; y_ < len; ++y_) {
    printf("%4d%s", ary[y_], (++c_ % bk == 0 ? "\n" : ""));
  }
  putchar('\n');
}

//  MARK: - Example from RosettaCode
// Get size of statically allocated array
#define ARR_LEN(ARR) (sizeof ARR / sizeof *ARR)
// Generate random number in the interval [M,N]
#define RAND_RNG(M,N) (M + rand() / (RAND_MAX / (N - M + 1) + 1));

inline
static void swap(unsigned * a, unsigned * b) {
  unsigned tmp = *a;
  *a = *b;
  *b = tmp;
}

/* sort unsigned ints */
static void rad_sort_u(unsigned * from, unsigned * to, unsigned bit)
{
	if (!bit || to < from + 1) {
    return;
  }

	unsigned * ll = from;
  unsigned * rr = to - 1;
	for (;;) {
		/* find left most with bit, and right most without bit, swap */
		while (ll < rr && !(*ll & bit)) {
      ll++;
    }

		while (ll < rr &&  (*rr & bit)) {
      rr--;
    }

		if (ll >= rr) {
      break;
    }

		swap(ll, rr);
	}

	if (!(bit & *ll) && ll < to) {
    ll++;
  }

	bit >>= 1;

	rad_sort_u(from, ll, bit);
	rad_sort_u(ll, to, bit);
}

/* sort signed ints: flip highest bit, sort as unsigned, flip back */
static void radix_sort(int * a, const size_t len)
{
	size_t i;
	unsigned * x = (unsigned*) a;

	for (i = 0; i < len; i++) {
    x[i] ^= INT_MIN;
  }

  rad_sort_u(x, x + len, INT_MIN);

  for (i = 0; i < len; i++) {
    x[i] ^= INT_MIN;
  }
}

//  MARK: main()
//  Blended calls to solutions.
int main(int argc, char const * argv[]) {

  //  ------------------------------------------------------
  // Rosettacode
  srand(time(NULL));
  int x[16];

  for (size_t i = 0; i < ARR_LEN(x); i++) {
    x[i] = RAND_RNG(-128, 127)
  }

  for (size_t i = 0; i < ARR_LEN(x); i++) {
    printf("%d%c", x[i], i + 1 < ARR_LEN(x) ? ' ' : '\n');
  }

  radix_sort(x, ARR_LEN(x));

  for (size_t i = 0; i < ARR_LEN(x); i++) {
    printf("%d%c", x[i], i + 1 < ARR_LEN(x) ? ' ' : '\n');
  }

  //  ------------------------------------------------------
  //  StackOverflow
  putchar('\n');
  {
    int samples[] = {
      38, 124, 67, 10,  28, 39, 54, 13,
      58,   1, 38, 72, 113, 25, 53, 23,
    };
    size_t samples_l = sizeof(samples) / sizeof(*samples);
    show_n_tell(samples_l, samples, 8);
    RadixSortA(samples_l, samples);
    show_n_tell(samples_l, samples, 8);
  }

  {
    int samples[] = {
      38, 124, 67, 10,  28, 39, 54, 13,
      58,   1, 38, 72, 113, 25, 53, 23,
    };
    size_t samples_l = sizeof(samples) / sizeof(*samples);
    show_n_tell(samples_l, samples, 8);
    RadixSortD(samples_l, samples);
    show_n_tell(samples_l, samples, 8);
  }

  {
    int samples[] = {
      38, 124, 67, 10,  28, 39, 54, 13,
      58,   1, 38, 72, 113, 25, 53, 23,
    };
    size_t samples_l = sizeof(samples) / sizeof(*samples);
    show_n_tell(samples_l, samples, 8);
    RadixSort(samples_l, samples, 'A');
    show_n_tell(samples_l, samples, 8);
  }

  {
    int samples[] = {
      38, 124, 67, 10,  28, 39, 54, 13,
      58,   1, 38, 72, 113, 25, 53, 23,
    };
    size_t samples_l = sizeof(samples) / sizeof(*samples);
    show_n_tell(samples_l, samples, 8);
    RadixSort(samples_l, samples, 'D');
    show_n_tell(samples_l, samples, 8);
  }

  return EXIT_SUCCESS;
}

//  MARK: - Example from StackOverflow
#define MAX 20
void RadixSortA(size_t len, int sort_this[len]) {
  int max = 0, exp = 1, work[MAX];

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
}

void RadixSortD(size_t len, int sort_this[len]) {
  int max = 0, exp = 1, work[MAX];

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
}

void RadixSort(size_t len, int sort_this[len], char dir) {
  int max = 0, exp = 1, work[MAX];

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
      work[--bucket[abs(adjust - sort_this[y_] / exp % 10)]] = sort_this[y_]; // changed this line
    }

    for (size_t i_ = 0; i_ < len; i_++) {
      sort_this[i_] = work[i_];              // changed this line
    }

    exp *= 10;
  }
}
