#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    int min = m < n ? m : n;
    long long total = 0;
    for (int i = 1; i <= min; i++) {
        total += (long long)(m - i + 1) * (n - i + 1);
    }
    return total;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 <= 0 || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 <= 0 || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int m = (int)val1;
    int n = (int)val2;
    
    long long result = count_squares(m, n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}