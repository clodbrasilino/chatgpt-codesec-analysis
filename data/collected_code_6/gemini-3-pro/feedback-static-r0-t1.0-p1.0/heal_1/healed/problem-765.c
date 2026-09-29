#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

unsigned long long find_nth_polite_number(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    return n + (unsigned long long)log2(n + (unsigned long long)log2(n));
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long long n = strtoull(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || n == 0) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = find_nth_polite_number(n);
    
    if (result < n) {
        fprintf(stderr, "Integer overflow occurred.\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}