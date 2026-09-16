#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2.5928571428571425, got 2.4500000476837158
  *  test case 2 failed: expected 3.547739657143682, got 3.4951081275939941
  *  test case 1 failed: expected 2.083333333333333, got 1.8333333730697632
  */

static double harmonic_sum(unsigned long n)
{
    double sum = 0.0;

    for (unsigned long i = 1; i < n; ++i) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long n = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || n == 0) {
        fprintf(stderr, "Invalid positive integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", harmonic_sum(n));
    return EXIT_SUCCESS;
}