#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t nth_jacobsthal_lucas(uint32_t n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    uint64_t a = 2, b = 1;
    for (uint32_t i = 2; i <= n; i++) {
        uint64_t c = a + 2 * b;
        if (c < a || c < 2 * b) {
            fprintf(stderr, "Integer overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Negative input is not allowed.\n");
        return EXIT_FAILURE;
    }

    uint64_t result = nth_jacobsthal_lucas((uint32_t)n);
    printf("The %" PRId32 "th Jacobsthal-L Lucas number is: %" PRIu64 "\n", n, result);

    return EXIT_SUCCESS;
}