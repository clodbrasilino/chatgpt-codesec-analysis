#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

long long sum_of_squares(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long term = (long long)i * i;
        if (sum > LLONG_MAX - term) {
            return -1;
        }
        sum += term;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *endptr;
    long val;
    int n;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0 || (len == sizeof(input_buffer) - 1 && input_buffer[len - 1] != '\n')) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long or empty. Please enter a smaller value.\n");
        return EXIT_FAILURE;
    }
    if (input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
    }

    errno = 0;
    val = strtol(input_buffer, &endptr, 10);

    if (endptr == input_buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Overflow occurred during computation.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares from 1 to %d is %lld\n", n, result);

    return EXIT_SUCCESS;
}