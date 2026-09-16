#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_squares_of_odds(unsigned int n) {
    unsigned long long max_n = (unsigned long long)((1ULL << 63) - 1) / 4ULL;
    if (n > max_n) {
        return 0;
    }
    return (unsigned long long)n * (2ULL * n - 1ULL) * (2ULL * n + 1ULL) / 3ULL;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  Assuming that condition 'val==0' is not redundant
     */
    if (*endptr != '\0' || val == 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'n=(unsigned int)val', assigned value is greater than 0
     */
    unsigned int n = (unsigned int)val;

    unsigned long long result = sum_of_squares_of_odds(n);

    /* Possible weaknesses found:
     *  Condition 'n!=0' is always true [knownConditionTrueFalse]
     *  Condition 'n!=0' is always true
     */
    if (result == 0 && n != 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}