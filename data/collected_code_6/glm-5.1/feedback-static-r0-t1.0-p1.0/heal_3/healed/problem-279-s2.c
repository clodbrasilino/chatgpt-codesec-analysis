#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_decagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return 4ULL * n * n - 3ULL * n;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > 65535 || val == 0) {
        fprintf(stderr, "Error: Invalid input. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = find_nth_decagonal_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}