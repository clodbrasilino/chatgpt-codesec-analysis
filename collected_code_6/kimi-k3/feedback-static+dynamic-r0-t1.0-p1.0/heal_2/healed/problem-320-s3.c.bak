#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long calculate_difference(long long n) {
    if (n > 1000000) {
        return -1;
    }
    
    long long sum = (n * (n + 1)) / 2;
    
    if (sum != 0 && (sum > LLONG_MAX / sum || sum < LLONG_MIN / sum)) {
        return -1;
    }
    long long squared_sum = sum * sum;
    
    if (n > LLONG_MAX / (n + 1)) {
        return -1;
    }
    long long temp = n * (n + 1);
    
    if (temp > LLONG_MAX / (2 * n + 1)) {
        return -1;
    }
    long long sum_of_squares = (temp * (2 * n + 1)) / 6;
    
    if ((sum_of_squares > 0 && squared_sum > LLONG_MAX - sum_of_squares) ||
        (sum_of_squares < 0 && squared_sum < LLONG_MIN - sum_of_squares)) {
        return -1;
    }
    
    return squared_sum - sum_of_squares;
}

int main(void) {
    char input_buffer[128];
    char *end_ptr = NULL;
    long long n = 0;
    long long result = 0;

    printf("Enter a natural number (n): ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoll(input_buffer, &end_ptr, 10);

    if (errno == ERANGE || n <= 0) {
        fprintf(stderr, "Error: Input must be a positive natural number within valid range.\n");
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer || (*end_ptr != '\n' && *end_ptr != '\0')) {
        fprintf(stderr, "Error: Invalid input format. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (n > 1000000) {
        fprintf(stderr, "Error: Input too large, calculation would exceed integer limits.\n");
        return EXIT_FAILURE;
    }

    result = calculate_difference(n);
    
    if (result == -1) {
        fprintf(stderr, "Error: Calculation overflow detected.\n");
        return EXIT_FAILURE;
    }
    
    printf("Difference: %lld\n", result);

    return EXIT_SUCCESS;
}