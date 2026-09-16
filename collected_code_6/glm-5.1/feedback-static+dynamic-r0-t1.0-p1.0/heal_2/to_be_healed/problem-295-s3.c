#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_divisors(unsigned long long n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long sum = 0;

    for (unsigned long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    unsigned long long num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    num = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || num == 0) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_of_divisors(num);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}