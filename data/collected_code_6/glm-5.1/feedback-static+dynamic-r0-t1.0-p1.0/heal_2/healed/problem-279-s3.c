#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_nth_decagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    long long ln = n;
    return 4 * ln * ln - 3 * ln;
}

int main(int argc, char * const * argv) {
    long long n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    n = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || n <= 0 || n > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = find_nth_decagonal_number((int)n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}