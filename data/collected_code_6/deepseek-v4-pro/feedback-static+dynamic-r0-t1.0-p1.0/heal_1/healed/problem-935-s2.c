#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_squares(int n) {
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
    char input_buffer[32];
    char *endptr;
    long val;
    int n;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input_buffer, &endptr, 10);

    if (endptr == input_buffer || *endptr != '\n') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Overflow occurred during computation.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares from 1 to %d is %lld\n", n, result);

    return EXIT_SUCCESS;
}