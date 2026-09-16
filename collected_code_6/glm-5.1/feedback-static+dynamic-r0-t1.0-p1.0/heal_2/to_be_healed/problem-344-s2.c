#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int count_odd_factors(int lower, int upper) {
    if (lower > upper) {
        return 0;
    }

    int count = 0;
    for (int i = lower; i <= upper; i++) {
        if (i <= 0) {
            continue;
        }
        int root = (int)sqrt(i);
        if (root * root == i) {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_lower, *endptr_upper;
    long lower_l = strtol(argv[1], &endptr_lower, 10);
    long upper_l = strtol(argv[2], &endptr_upper, 10);

    if (*endptr_lower != '\0' || *endptr_upper != '\0') {
        fprintf(stderr, "Invalid input: arguments must be integers\n");
        return EXIT_FAILURE;
    }

    if (lower_l > INT_MAX || upper_l > INT_MAX || lower_l < INT_MIN || upper_l < INT_MIN) {
        fprintf(stderr, "Invalid input: arguments out of int range\n");
        return EXIT_FAILURE;
    }

    int lower = (int)lower_l;
    int upper = (int)upper_l;

    int result = count_odd_factors(lower, upper);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}