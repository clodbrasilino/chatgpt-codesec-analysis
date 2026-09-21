#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

static long long sum_of_squares(int n) {
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
    char *input_line = NULL;
    size_t input_size = 0;
    char *endptr;
    long val;
    int n;

    printf("Enter a positive integer: ");
    if (getline(&input_line, &input_size, stdin) == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input_line);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input_line);
    if (len == 0 || input_line[0] == '\n') {
        fprintf(stderr, "Input is empty. Please enter a non-negative integer.\n");
        free(input_line);
        return EXIT_FAILURE;
    }

    if (input_line[len - 1] == '\n') {
        input_line[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    errno = 0;
    val = strtol(input_line, &endptr, 10);

    if (endptr == input_line || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        free(input_line);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        free(input_line);
        return EXIT_FAILURE;
    }

    n = (int)val;

    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Overflow occurred during computation.\n");
        free(input_line);
        return EXIT_FAILURE;
    }

    printf("Sum of squares from 1 to %d is %lld\n", n, result);

    free(input_line);
    return EXIT_SUCCESS;
}