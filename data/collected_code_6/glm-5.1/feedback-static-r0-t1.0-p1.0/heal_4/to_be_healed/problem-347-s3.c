#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }
    
    unsigned long long count = 0;
    while (n > 0) {
        count += (unsigned long long)m * n;
        m--;
        n--;
    }
    
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 <= 0 || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 <= 0 || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", count_squares((int)val1, (int)val2));
    
    return EXIT_SUCCESS;
}