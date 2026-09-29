#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

int arithmetic_progression_nth_term(int first_term, int common_difference, int n) {
    if (n < 1) {
        fprintf(stderr, "Error: Term position must be positive\n");
        exit(EXIT_FAILURE);
    }

    if (n > 1) {
        long long step = (long long)(n - 1) * common_difference;
        if (step > INT_MAX || step < INT_MIN) {
            fprintf(stderr, "Error: Integer overflow in computation\n");
            exit(EXIT_FAILURE);
        }
        long long result = (long long)first_term + step;
        if (result > INT_MAX || result < INT_MIN) {
            fprintf(stderr, "Error: Integer overflow in final result\n");
            exit(EXIT_FAILURE);
        }
    }

    return first_term + (n - 1) * common_difference;
}

int safe_read_int(const char *prompt, int *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256] = {0};
    char *endptr;
    long val;
    size_t len;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len == 0 || (len == 1 && buffer[0] == '\n')) {
        return 0;
    }

    if (buffer[len - 1] != '\n') {
        if (len == sizeof(buffer) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
        return 0;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 0;
    }

    *value = (int)val;
    return 1;
}

int main(void) {
    int first_term;
    int common_difference;
    int n;
    int result;

    if (!safe_read_int("Enter first term: ", &first_term)) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    if (!safe_read_int("Enter common difference: ", &common_difference)) {
        fprintf(stderr, "Error: Invalid input for common difference\n");
        return EXIT_FAILURE;
    }

    if (!safe_read_int("Enter term position: ", &n)) {
        fprintf(stderr, "Error: Invalid input for term position\n");
        return EXIT_FAILURE;
    }

    result = arithmetic_progression_nth_term(first_term, common_difference, n);
    printf("The %d-th term is: %d\n", n, result);

    return EXIT_SUCCESS;
}