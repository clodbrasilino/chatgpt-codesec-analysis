#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long count_squares(unsigned int m, unsigned int n) {
    unsigned long long count = 0;
    unsigned int min = m < n ? m : n;
    for (unsigned int i = 1; i <= min; i++) {
        count += (unsigned long long)(m - i + 1) * (n - i + 1);
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    errno = 0;
    unsigned long val1 = strtoul(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0' || val1 == 0 || val1 > UINT_MAX) {
        fprintf(stderr, "Error: Dimensions must be positive integers within valid range.\n");
        return EXIT_FAILURE;
    }
    
    char *endptr2;
    errno = 0;
    unsigned long val2 = strtoul(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0' || val2 == 0 || val2 > UINT_MAX) {
        fprintf(stderr, "Error: Dimensions must be positive integers within valid range.\n");
        return EXIT_FAILURE;
    }
    
    unsigned int m = (unsigned int)val1;
    unsigned int n = (unsigned int)val2;
    
    printf("%llu\n", count_squares(m, n));
    
    return EXIT_SUCCESS;
}