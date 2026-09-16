#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int arithmetic_progression(int first_term, int common_difference, int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    return first_term + (n - 1) * common_difference;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_difference> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;

    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }

    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }

    long val3 = strtol(argv[3], &endptr3, 10);
    if (*endptr3 != '\0' || val3 <= 0 || val3 > INT_MAX) {
        return EXIT_FAILURE;
    }

    int first_term = (int)val1;
    int common_difference = (int)val2;
    int n = (int)val3;

    int result = arithmetic_progression(first_term, common_difference, n);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}