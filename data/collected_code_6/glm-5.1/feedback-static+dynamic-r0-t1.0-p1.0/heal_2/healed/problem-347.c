#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char * const argv[const]) {
    unsigned int m, n;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <m> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t len1 = strlen(argv[1]);
    size_t len2 = strlen(argv[2]);
    if (len1 == 0 || len1 > 10 || len2 == 0 || len2 > 10) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%u", &m) != 1 || sscanf(argv[2], "%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%llu\n", count_squares(m, n));
    return EXIT_SUCCESS;
}