#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

uint64_t sum_fourth_power_even(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        uint64_t even = 2ULL * i;
        uint64_t square = even * even;
        uint64_t fourth = square * square;
        if (sum > UINT64_MAX - fourth) {
            return UINT64_MAX;
        }
        sum += fourth;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }
    if (len == 0 || input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {}
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(input, &endptr, 10);

    if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (val < 1 || val > 1000000) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    uint64_t result = sum_fourth_power_even(n);
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow detected.\n");
        return EXIT_FAILURE;
    }
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}