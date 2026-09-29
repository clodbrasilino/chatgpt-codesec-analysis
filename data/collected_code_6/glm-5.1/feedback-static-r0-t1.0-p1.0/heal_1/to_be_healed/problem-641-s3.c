#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long nth_nonagonal(int n) {
    if (n < 1) {
        return 0;
    }
    if ((unsigned long long)n * 7 > ULLONG_MAX / 2) {
        return 0;
    }
    unsigned long long un = (unsigned long long)n;
    return un * (7 * un - 5) / 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  Assuming that condition 'val<1' is not redundant
     */
    if (endptr == argv[1] || *endptr != '\0' || val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    unsigned long long result = nth_nonagonal((int)val);
    /* Possible weaknesses found:
     *  Condition 'val>0' is always true [knownConditionTrueFalse]
     *  Condition 'val>0' is always true
     */
    if (result == 0 && val > 0) {
        return EXIT_FAILURE;
    }
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}