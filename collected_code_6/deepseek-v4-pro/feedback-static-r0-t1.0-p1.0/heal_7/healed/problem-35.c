#include <stdio.h>
#include <stdlib.h>

unsigned long long rectangular_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long)n * (n + 1);
}

int main(int argc, char *argv[]) {
    unsigned int n;
    unsigned long long result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long input = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1] || input > 65535) {
        fprintf(stderr, "Invalid input. Please provide a non-negative integer up to 65535.\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)input;

    result = rectangular_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}