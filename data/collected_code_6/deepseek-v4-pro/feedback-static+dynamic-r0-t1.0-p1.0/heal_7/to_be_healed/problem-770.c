#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

static unsigned long long sum_of_fourth_power_odd(unsigned int n) {
    unsigned long long sum = 0;
    unsigned long long odd = 1;
    unsigned int i;

    for (i = 0; i < n; ++i) {
        unsigned long long square;
        unsigned long long fourth;

        if (odd > ULLONG_MAX / odd) {
            return ULLONG_MAX;
        }
        square = odd * odd;

        if (square > ULLONG_MAX / square) {
            return ULLONG_MAX;
        }
        fourth = square * square;

        if (ULLONG_MAX - fourth < sum) {
            return ULLONG_MAX;
        }
        sum += fourth;

        if (odd > ULLONG_MAX - 2) {
            break;
        }
        odd += 2;
    }

    return sum;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    char *endptr;
    unsigned long val;
    unsigned int n;

    printf("Enter the number of odd natural numbers: ");
    read = getline(&input, &len, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    }

    if (read == 0 || input[0] == '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        free(input);
        return EXIT_FAILURE;
    }

    {
        size_t i;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t input_len = read;
        for (i = 0; i < input_len; i++) {
            if (!isdigit((unsigned char)input[i])) {
                fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
                free(input);
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    val = strtoul(input, &endptr, 10);
    if (errno == ERANGE || val > UINT_MAX) {
        fprintf(stderr, "Input out of range. Please enter a smaller non-negative integer.\n");
        free(input);
        return EXIT_FAILURE;
    }
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        free(input);
        return EXIT_FAILURE;
    }

    n = (unsigned int)val;

    {
        unsigned long long result = sum_of_fourth_power_odd(n);
        if (result == ULLONG_MAX && n > 0) {
            printf("Result overflowed for the given input.\n");
            free(input);
            return EXIT_FAILURE;
        }

        printf("Sum of fourth powers of first %u odd natural numbers: %llu\n",
               n, result);
    }

    free(input);
    return EXIT_SUCCESS;
}