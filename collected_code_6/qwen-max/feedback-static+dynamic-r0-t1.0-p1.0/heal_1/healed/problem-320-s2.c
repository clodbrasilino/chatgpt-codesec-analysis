#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

bool is_valid(long long n) {
    if (n <= 0 || n > 1414213562) {
        return false;
    }
    return true;
}

long long safe_multiply(long long a, long long b) {
    if (a > 0 && b > 0 && a > LLONG_MAX / b) {
        return LLONG_MAX;
    }
    if (a < 0 && b < 0 && a < LLONG_MIN / b) {
        return LLONG_MIN;
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a) {
        return LLONG_MIN;
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b) {
        return LLONG_MIN;
    }
    return a * b;
}

long long square_sum(long long n) {
    long long sum = n * (n + 1) / 2;
    return safe_multiply(sum, sum);
}

long long sum_of_squares(long long n) {
    long long term1 = safe_multiply(n, n + 1);
    long long term2 = safe_multiply(2 * n + 1, 6);
    return safe_multiply(term1, term2);
}

long long calculate_difference(long long n) {
    if (!is_valid(n)) {
        return -1;
    }
    return square_sum(n) - sum_of_squares(n);
}

int main() {
    long long n, result;
    printf("Enter a positive integer: ");
    if (scanf("%lld", &n) != 1 || !is_valid(n)) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    result = calculate_difference(n);
    if (result == -1) {
        fprintf(stderr, "Calculation error.\n");
        return 1;
    }
    printf("The result is: %lld\n", result);
    return 0;
}