#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_min_sum_of_factors(int n) {
    if (n <= 1) {
        return n;
    }

    int sum = 0;
    int remaining = n;

    for (int i = 2; i * i <= remaining; i++) {
        while (remaining % i == 0) {
            sum += i;
            remaining /= i;
        }
    }

    if (remaining > 1) {
        sum += remaining;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;

    if (argc == 2) {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        n = (int)val;
    } else {
        if (scanf("%d", &n) != 1) {
            return EXIT_FAILURE;
        }
    }

    int result = find_min_sum_of_factors(n);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}