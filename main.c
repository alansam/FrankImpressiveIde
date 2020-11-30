//  @see: https://rosettacode.org/wiki/Sorting_algorithms/Radix_sort#C
//  @see: https://stackoverflow.com/questions/33657031/radix-sort-descending

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "radix.h"

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
    puts("sort 1 [ascending]");
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
    puts("sort 2 [descending]");
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
    puts("sort 3 [ascending]");
    int samples[] = {
      -38, 124, -67, 10,  -28, 39,  54, -13,
       58,   1,  38, 72, -113, 25, -53,  23,
    };
    size_t samples_l = sizeof(samples) / sizeof(*samples);

    show_n_tell(samples_l, samples, 8);
    RadixSort(samples_l, samples, 'A');
    show_n_tell(samples_l, samples, 8);
  }

  {
    puts("sort 4 [descending]");
    int samples[] = {
      -38, 124, -67, 10,  -28, 39,  54, -13,
       58,   1,  38, 72, -113, 25, -53,  23,
    };
    size_t samples_l = sizeof(samples) / sizeof(*samples);

    show_n_tell(samples_l, samples, 8);
    RadixSort(samples_l, samples, 'D');
    show_n_tell(samples_l, samples, 8);
  }

  return EXIT_SUCCESS;
}
