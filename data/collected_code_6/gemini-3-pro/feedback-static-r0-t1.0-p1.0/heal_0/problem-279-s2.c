#include <stdio.h>
#include <stdlib.h>

unsigned long long nth_decagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long)n * (4ULL * n - 3ULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n_input = atoi(argv[1]);
    if (n_input < 0) {
        fprintf(stderr, "Error: n must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)n_input;
    unsigned long long result = nth_decagonal_number(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}