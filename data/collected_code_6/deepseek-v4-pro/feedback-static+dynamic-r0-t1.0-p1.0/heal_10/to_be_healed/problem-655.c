#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stddef.h>

static int safe_multiply(int a, int b, long long *result) {
    long long temp = (long long)a * b;
    if (a != 0 && (temp / a) != b) {
        return 0;
    }
    *result = temp;
    return 1;
}

static int safe_add(long long a, long long b, long long *result) {
    if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
        return 0;
    }
    *result = a + b;
    return 1;
}

static int int_pow5(int base, long long *result) {
    long long temp = base;
    long long final_result = 1;
    long long mult_result;

    for (int i = 0; i < 5; i++) {
        if (!safe_multiply((int)final_result, (int)temp, &mult_result)) {
            return 0;
        }
        final_result = mult_result;
    }

    *result = final_result;
    return 1;
}

static long long sum_of_fifth_powers(int n, int *error) {
    long long total = 0;
    long long power_result;
    long long add_result;

    if (n < 0) {
        *error = EINVAL;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        int status = int_pow5(i, &power_result);
        if (status == 0) {
            *error = EOVERFLOW;
            return 0;
        }

        status = safe_add(total, power_result, &add_result);
        if (status == 0) {
            *error = EOVERFLOW;
            return 0;
        }
        total = add_result;
    }

    *error = 0;
    return total;
}

#define INPUT_BUFFER_SIZE 256

int main(void) {
    int n;
    long long result;
    int error;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_line[INPUT_BUFFER_SIZE];
    char *endptr;
    size_t input_length;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    input_line[0] = '\0';

    printf("Enter a non-negative integer n: ");
    if (fgets(input_line, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input_length = strnlen(input_line, INPUT_BUFFER_SIZE);

    if (input_length > 0 && input_line[input_length - 1] == '\n') {
        input_line[input_length - 1] = '\0';
        input_length--;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (input_length >= INPUT_BUFFER_SIZE - 1) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    if (input_length == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < input_length; i++) {
        unsigned char ch = (unsigned char)input_line[i];
        if (i == 0 && input_line[i] == '-') {
            continue;
        }
        if (!isdigit(ch) && ch != '\t') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    if (input_line[0] == '-' && input_length == 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input_length > 1 && input_line[0] == '0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long long parsed = strtoll(input_line, &endptr, 10);

    if (errno == ERANGE || endptr == input_line || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (parsed < 0 || parsed > INT_MAX) {
        fprintf(stderr, "n must be a non-negative integer within valid range\n");
        return EXIT_FAILURE;
    }

    n = (int)parsed;

    result = sum_of_fifth_powers(n, &error);

    if (error != 0) {
        fprintf(stderr, "Overflow occurred while calculating the sum\n");
        return EXIT_FAILURE;
    }

    printf("Sum of fifth powers from 1 to %d is: %lld\n", n, result);
    return EXIT_SUCCESS;
}