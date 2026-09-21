#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long get_star_number(int n) {
    if (n < 1) {
        return 0;
    }

    unsigned long long term = 6ULL * (unsigned long long)(n - 1);
    
    if (term > ULLONG_MAX / (term + 1)) {
        return 0;
    }
    
    unsigned long long product = term * (term + 1);
    
    if (product / 2 > ULLONG_MAX - 1ULL) {
        return 0;
    }
    
    unsigned long long result = 1ULL + product / 2;

    return result;
}

int main(int argc, char * const * argv) {
    long n;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    n = strtol(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  Assuming that condition 'n<1' is not redundant
     */
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || n < 1 || n > INT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned long long s = get_star_number((int)n);

    /* Possible weaknesses found:
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Condition 'n>0' is always true
     */
    if (s == 0 && n > 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", s);

    return EXIT_SUCCESS;
}