#include <stdio.h>
#include <stdlib.h>

static long long count_sequences(long long m, long long n)
{
    if (n == 0) {
        return 1;
    }
    if (m <= 0) {
        return 0;
    }
    return count_sequences(m - 1, n) + count_sequences(m / 2, n - 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000002,time:3843,execs:193,op:havoc,rep:2; likely memory-safety defect
  */

int main(void)
{
    long long m;
    long long n;
    long long result;

    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Failed to read input values\n");
        return EXIT_FAILURE;
    }

    if (m < 0 || n < 0) {
        fprintf(stderr, "Invalid input values\n");
        return EXIT_FAILURE;
    }

    result = count_sequences(m, n);

    if (printf("Number of possible sequences: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}