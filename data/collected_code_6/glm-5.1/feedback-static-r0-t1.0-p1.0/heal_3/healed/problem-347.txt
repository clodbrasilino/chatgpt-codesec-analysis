#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    unsigned long long count = 0;
    unsigned int min = m < n ? m : n;
    for (unsigned int i = 1; i <= min; i++) {
        count += (unsigned long long)(m - i + 1) * (n - i + 1);
    }
    return count;
}

int main(int argc, char * const * argv) {
    unsigned int m, n;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <m> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    char *endptr2;
    unsigned long long val1 = strtoull(argv[1], &endptr1, 10);
    unsigned long long val2 = strtoull(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 == 0 || val2 == 0 || val1 > 4294967295ULL || val2 > 4294967295ULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    m = (unsigned int)val1;
    n = (unsigned int)val2;
    printf("%llu\n", count_squares(m, n));
    return EXIT_SUCCESS;
}