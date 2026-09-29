#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    printf("Difference: %lld\n", result);

    return EXIT_SUCCESS;
}