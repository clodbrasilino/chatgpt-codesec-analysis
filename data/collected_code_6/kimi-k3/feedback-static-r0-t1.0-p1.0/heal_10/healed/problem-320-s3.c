#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long calculate_difference(long long n) {
    long long sum = (n * (n + 1)) / 2;
    long long squared_sum = sum * sum;
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;
    return squared_sum - sum_of_squares;
}

int main(void) {
    char *input_buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    char *end_ptr = NULL;
    long long n = 0;
    long long result = 0;

    printf("Enter a natural number (n): ");

    len = getline(&input_buffer, &buffer_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error: Failed to read input.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
    }

    errno = 0;
    n = strtoll(input_buffer, &end_ptr, 10);

    if (errno == ERANGE || n <= 0) {
        fprintf(stderr, "Error: Input must be a positive natural number within valid range.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer || *end_ptr != '\0') {
        fprintf(stderr, "Error: Invalid input format. Please enter a valid integer.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    if (n > 1000000) {
        fprintf(stderr, "Error: Input too large, calculation would exceed integer limits.\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    result = calculate_difference(n);
    printf("Difference: %lld\n", result);

    free(input_buffer);
    return EXIT_SUCCESS;
}