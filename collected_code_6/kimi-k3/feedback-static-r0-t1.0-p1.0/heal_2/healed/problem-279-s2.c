#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

uint64_t decagonal_number(uint64_t n) {
    return 4 * n * n - 3 * n;
}

int main(void) {
    uint64_t n;
    char input[32];
    char *endptr;

    printf("Enter the value of n: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    errno = 0;
    n = strtoull(input, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Input out of range.\n");
        return 1;
    }

    if (endptr == input) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Error: Invalid input. Please enter only a positive integer.\n");
        return 1;
    }

    if (n > 2147483647ULL) {
        fprintf(stderr, "Error: Input too large. Maximum value is 2147483647.\n");
        return 1;
    }

    uint64_t decagonal = decagonal_number(n);
    printf("The %" PRIu64 "th decagonal number is: %" PRIu64 "\n", n, decagonal);

    return 0;
}