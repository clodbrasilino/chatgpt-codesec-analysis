#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

#define INPUT_SIZE 256U

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    unsigned long long a;
    unsigned long long b;

    if (sum == NULL || average == NULL || n == 0ULL || n == ULLONG_MAX) {
        return -1;
    }

    a = n;
    b = n + 1ULL;

    if ((a & 1ULL) == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return -1;
    }

    *sum = a * b;
    *average = ((long double)n + 1.0L) / 2.0L;

    return 0;
}

static int discard_remaining_input(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard_buffer[INPUT_SIZE];

    for (;;) {
        if (fgets(discard_buffer, (int)sizeof discard_buffer, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strchr'
         */
        if (strchr(discard_buffer, '\n') != NULL) {
            return 0;
        }
    }
}

static int read_input(char *buffer, size_t size)
{
    char *newline;
    int discard_result;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    discard_result = discard_remaining_input();
    if (discard_result < 0) {
        return -1;
    }

    return 1;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int read_result;
    int exit_status = EXIT_FAILURE;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    read_result = read_input(input, INPUT_SIZE);

    if (read_result < 0) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (read_result > 0) {
        fputs("Input is too large.\n", stderr);
        goto cleanup;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Input must be a positive integer.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == NULL || end == start) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0' || n == 0ULL) {
        fputs("Input must be a positive integer.\n", stderr);
        goto cleanup;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        fputs("The result is outside the supported range.\n", stderr);
        goto cleanup;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(input);
    return exit_status;
}