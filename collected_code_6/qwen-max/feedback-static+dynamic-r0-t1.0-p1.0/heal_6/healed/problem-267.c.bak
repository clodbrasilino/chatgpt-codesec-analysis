#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

bool is_valid_positive_integer(const char *str) {
    if (str == NULL || str[0] == '\0') return false;
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

int64_t sum_of_squares(int64_t n) {
    int64_t sum = 0;
    for (int64_t i = 1; i <= n; i++) {
        int64_t odd_number = 2 * i - 1;
        int64_t square = odd_number * odd_number;
        if (square > 0 && (INT64_MAX - square) >= sum) {
            sum += square;
        } else {
            printf("Overflow detected.\n");
            exit(1);
        }
    }
    return sum;
}

int main() {
    char input[12];
    int64_t n;

    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL || !is_valid_positive_integer(input)) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    char *endptr;
    errno = 0;
    long n_long = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || *endptr != '\0' || n_long < 1 || n_long > INT64_MAX) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    n = (int64_t)n_long;

    int64_t result = sum_of_squares(n);
    printf("The sum of squares of the first %" PRId64 " odd natural numbers is: %" PRId64 "\n", n, result);

    return 0;
}