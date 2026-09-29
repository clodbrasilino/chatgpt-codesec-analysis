#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_octagonal(unsigned long long n) {
    return n * (3 * n - 2);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val == 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = find_nth_octagonal(val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}