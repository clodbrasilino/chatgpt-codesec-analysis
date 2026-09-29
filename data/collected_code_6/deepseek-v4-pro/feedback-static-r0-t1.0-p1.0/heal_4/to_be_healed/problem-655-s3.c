#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

unsigned long long sum_fifth_power(int n) {
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i * i * i;
        sum += term;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *endptr;

    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len >= sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    endptr = input;
    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr == '\0') {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long val = strtol(endptr, &endptr, 10);

    if (endptr == input || (*endptr != '\0' && !isspace((unsigned char)*endptr))) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Number out of range.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;

    if (n <= 0) {
        fprintf(stderr, "Number must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fifth powers: %llu\n", sum_fifth_power(n));
    return EXIT_SUCCESS;
}