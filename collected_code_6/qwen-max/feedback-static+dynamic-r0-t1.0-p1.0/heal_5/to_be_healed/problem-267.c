#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

bool is_valid_positive_integer(const char *str) {
    if (str == NULL || str[0] == '\0') return false;
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

int sum_of_squares(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int odd_number = 2 * i - 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2146453540 + 5499025 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:283,execs:147,op:havoc,rep:5)
         */
        sum += odd_number * odd_number;
    }
    return sum;
}

int main() {
    char input[12];
    int n;

    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL || !is_valid_positive_integer(input)) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    char *endptr;
    errno = 0;
    long n_long = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || *endptr != '\0' || n_long < 1 || n_long > INT_MAX) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    n = (int)n_long;

    int result = sum_of_squares(n);
    printf("The sum of squares of the first %d odd natural numbers is: %d\n", n, result);

    return 0;
}