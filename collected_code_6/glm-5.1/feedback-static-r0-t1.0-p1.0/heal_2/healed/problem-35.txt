#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long find_nth_rectangular_number(unsigned int n) {
    return (unsigned long long)n * (n + 1);
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Error: Invalid input. Must be a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = find_nth_rectangular_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}