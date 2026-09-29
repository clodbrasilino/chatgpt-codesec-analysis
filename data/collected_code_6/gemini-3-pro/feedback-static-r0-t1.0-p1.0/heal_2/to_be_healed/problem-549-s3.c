#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long sumOfFifthPowerOfOddNumbers(unsigned int n) {
    unsigned long long sum = 0;
    unsigned long long current_odd = 1;
    unsigned int i;

    for (i = 0; i < n; i++) {
        unsigned long long power = current_odd * current_odd * current_odd * current_odd * current_odd;
        sum += power;
        current_odd += 2;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    unsigned int n;
    unsigned long long result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0) {
        fprintf(stderr, "Invalid input. Please provide a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)val;
    result = sumOfFifthPowerOfOddNumbers(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}