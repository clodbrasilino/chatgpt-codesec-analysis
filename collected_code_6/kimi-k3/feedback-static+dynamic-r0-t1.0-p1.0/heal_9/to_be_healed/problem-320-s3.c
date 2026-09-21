#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
#include <stdint.h>

long long calculate_difference(long long n) {
    if (n <= 0) {
        return 0;
    }

    long long squared_sum;
    long long sum_of_squares;

    if (n % 2 == 0) {
        long long n_half = n / 2;
        if (n_half > LLONG_MAX / (n + 1)) {
            return 0;
        }
        long long sum = n_half * (n + 1);
        if (sum > 0 && sum <= LLONG_MAX / sum) {
            squared_sum = sum * sum;
        } else {
            return 0;
        }
    } else {
        long long n_plus_1_half = (n + 1) / 2;
        if (n > LLONG_MAX / n_plus_1_half) {
            return 0;
        }
        long long sum = n * n_plus_1_half;
        if (sum > 0 && sum <= LLONG_MAX / sum) {
            squared_sum = sum * sum;
        } else {
            return 0;
        }
    }

    long long a = n;
    long long b = n + 1;
    long long c = 2 * n + 1;

    if (a % 6 == 0) {
        a /= 6;
    } else if (b % 6 == 0) {
        b /= 6;
    } else if (c % 6 == 0) {
        c /= 6;
    } else if (a % 3 == 0 && b % 2 == 0) {
        a /= 3;
        b /= 2;
    } else if (a % 3 == 0 && c % 2 == 0) {
        a /= 3;
        c /= 2;
    } else if (b % 3 == 0 && a % 2 == 0) {
        b /= 3;
        a /= 2;
    } else if (b % 3 == 0 && c % 2 == 0) {
        b /= 3;
        c /= 2;
    } else if (c % 3 == 0 && a % 2 == 0) {
        c /= 3;
        a /= 2;
    } else if (c % 3 == 0 && b % 2 == 0) {
        c /= 3;
        b /= 2;
    }

    if (a != 0 && b > LLONG_MAX / a) {
        return 0;
    }
    long long ab = a * b;

    if (ab != 0 && c > LLONG_MAX / ab) {
        return 0;
    }
    sum_of_squares = ab * c;

    return squared_sum - sum_of_squares;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end_ptr = NULL;
    long long n = 0;
    long long result = 0;
    size_t input_length;
    int newline_found = 0;

    printf("Enter a natural number (n): ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    input_length = strlen(input_buffer);
    
    if (input_length > 0 && input_buffer[input_length - 1] == '\n') {
        newline_found = 1;
        input_buffer[input_length - 1] = '\0';
    }

    if (!newline_found && input_length == sizeof(input_buffer) - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
        fprintf(stderr, "Error: Input too long.\n");
        return EXIT_FAILURE;
    }

    if (input_buffer[0] == '\0') {
        fprintf(stderr, "Error: Input must be a positive natural number within valid range.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoll(input_buffer, &end_ptr, 10);

    if (errno == ERANGE || n <= 0) {
        fprintf(stderr, "Error: Input must be a positive natural number within valid range.\n");
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer || *end_ptr != '\0') {
        fprintf(stderr, "Error: Invalid input format. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (n > 1000000) {
        fprintf(stderr, "Error: Input too large, calculation would exceed integer limits.\n");
        return EXIT_FAILURE;
    }

    result = calculate_difference(n);
    printf("Difference: %lld\n", result);

    return EXIT_SUCCESS;
}