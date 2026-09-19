#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t sum_of_cubes(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (sum > INT64_MAX / i - i * i) {
            printf("Overflow detected in sum_of_cubes\n");
            return -1;
        }
        sum += (int64_t)i * i * i;
    }
    return sum;
}

int64_t sum_of_numbers(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (sum > INT64_MAX - i) {
            printf("Overflow detected in sum_of_numbers\n");
            return -1;
        }
        sum += i;
    }
    return sum;
}

int64_t difference(int n) {
    int64_t cubes_sum = sum_of_cubes(n);
    int64_t numbers_sum = sum_of_numbers(n);
    if (cubes_sum == -1 || numbers_sum == -1) {
        return -1;
    }
    if (cubes_sum < numbers_sum) {
        printf("Underflow detected in difference\n");
        return -1;
    }
    return cubes_sum - numbers_sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int64_t diff = difference(n);
    if (diff == -1) {
        printf("Error in calculation\n");
        return 1;
    }
    printf("The difference is: %ld\n", diff);

    return 0;
}