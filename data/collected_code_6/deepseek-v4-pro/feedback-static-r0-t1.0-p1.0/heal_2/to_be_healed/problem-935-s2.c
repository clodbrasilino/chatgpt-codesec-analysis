#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long sum_of_squares(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i;
    }
    return sum;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[64];
    char *endptr;
    long val;
    size_t len;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input_buffer, &endptr, 10);

    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }

    if (endptr == input_buffer) {
        fprintf(stderr, "Invalid input. No digits found.\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (*endptr != '\n' && *endptr != '\r' && *endptr != ' ') {
            fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    n = (int)val;

    printf("Sum of squares from 1 to %d is %lld\n", n, sum_of_squares(n));

    return EXIT_SUCCESS;
}