#include <stdio.h>
#include <stdlib.h>

unsigned long long rectangular_number(unsigned int n) {
    return (unsigned long long)n * ((unsigned long long)n + 1ULL);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long input = strtoul(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid unsigned integer.\n");
        return EXIT_FAILURE;
    }

    if (input > 4294967295UL) {
        fprintf(stderr, "Input too large for unsigned int.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)input;
    unsigned long long result = rectangular_number(n);

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}