#include <stdio.h>
#include <stdlib.h>

int compute_digit_sum(int n) {
    int sum = 0;
    int abs_n = abs(n);
    while (abs_n > 0) {
        sum += abs_n % 10;
        abs_n /= 10;
    }
    return sum;
}

int* compute_digit_sums(const int* numbers, size_t count) {
    if (numbers == NULL || count == 0) {
        return NULL;
    }

    int* sums = (int*)malloc(count * sizeof(int));
    if (sums == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        sums[i] = compute_digit_sum(numbers[i]);
    }

    return sums;
}

int main(void) {
    int numbers[] = {123, -456, 789, 0, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    int* sums = compute_digit_sums(numbers, count);
    if (sums == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("%d\n", sums[i]);
    }

    free(sums);
    sums = NULL;

    return EXIT_SUCCESS;
}