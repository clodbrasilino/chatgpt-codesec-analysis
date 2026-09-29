#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_of_fifth_power_odd(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    int count = 0;
    unsigned int num = 1;

    while (count < n) {
        unsigned long long term = (unsigned long long)num * num * num * num * num;
        if (sum > ULLONG_MAX - term) {
            return 0;
        }
        sum += term;
        num += 2;
        count++;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Invalid input: Not an integer\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Invalid input: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_of_fifth_power_odd(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}