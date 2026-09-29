#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_input_valid(int n) {
    return n > 0;
}

int64_t safe_cube_sum_of_odds(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        int64_t odd_number = 2 * i - 1;
        int64_t cube = odd_number * odd_number * odd_number;
        if (sum > INT64_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || !is_input_valid(n)) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    int64_t result = safe_cube_sum_of_odds(n);
    if (result == -1) {
        fprintf(stderr, "Overflow occurred. The result is too large to be represented.\n");
        return 1;
    }
    printf("The cube sum of the first %d odd natural numbers is: %lld\n", n, result);
    return 0;
}