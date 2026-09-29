#include <stdio.h>
#include <stdlib.h>

unsigned long long get_jacobsthal(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n > 64) {
        return 0;
    }

    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;

    for (unsigned int i = 2; i <= n; ++i) {
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(int argc, const char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)strtoul(argv[1], NULL, 10);
    
    if (n > 64) {
        fprintf(stderr, "Error: Input exceeds maximum supported value to prevent overflow.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = get_jacobsthal(n);
    if (printf("%llu\n", result) < 0) {
        fprintf(stderr, "Error: Failed to output the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}