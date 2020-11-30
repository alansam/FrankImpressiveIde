#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

void RadixSortA(int a[], size_t n);
void RadixSortD(int a[], size_t n);

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

inline
static void show_n_tell(size_t const len, int const ary[len],
                        size_t const bk) {
  for (size_t y_ = 0, c_ = 0; y_ < len; ++y_) {
    printf("%4d%s", ary[y_], (++c_ % bk == 0 ? "\n" : ""));
  }
  putchar('\n');
}
int main(int argc, char const * argv[]) {

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

  putchar('\n');
  int samples[] = {
    38, 124, 67, 10,  28, 39, 54, 13,
    58,   1, 38, 72, 113, 25, 53, 23,
  };
  size_t samples_l = sizeof(samples) / sizeof(*samples);
  show_n_tell(samples_l, samples, 8);
  RadixSortA(samples, samples_l);
  show_n_tell(samples_l, samples, 8);

  int simples[] = {
    38, 124, 67, 10,  28, 39, 54, 13,
    58,   1, 38, 72, 113, 25, 53, 23,
  };
  size_t simples_l = sizeof(simples) / sizeof(*simples);
  show_n_tell(simples_l, simples, 8);
  RadixSortD(simples, simples_l);
  show_n_tell(simples_l, simples, 8);

  return EXIT_SUCCESS;
}

#define MAX 20
void RadixSortA(int a[], size_t n) {
    int i, m = 0, exp = 1, b[MAX];
    for (i = 0; i < n; i++)
    {
        if (a[i] > m)
            m = a[i];
    }
    while (m / exp > 0)
    {
        int bucket[10] = { 0, };
        for (i = 0; i < n; i++) {
          bucket[a[i] / exp % 10]++;
        }
        for (i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            b[--bucket[a[i] / exp % 10]] = a[i];
        }
        for (i = 0; i < n; i++) {
            a[i] = b[i];
        }
        exp *= 10;
    }
}

void RadixSortD(int a[], size_t n) {
  int i, m = 0, exp = 1, b[MAX];
  for (i = 0; i < n; i++) {
    if (a[i] > m) {
      m = a[i];
    }
  }

  while (m / exp > 0)
  {
    int bucket[10]={0};
    for (i = 0; i < n; i++) {
      bucket[9 - a[i] / exp % 10]++;         // changed this line
    }
    for (i = 1; i < 10; i++) {
      bucket[i] += bucket[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
      b[--bucket[9 - a[i] / exp % 10]] = a[i]; // changed this line
    }
    for (i = 0; i < n; i++) {
      a[i] = b[i];                       // changed this line
    }

    exp *= 10;
  }
}
