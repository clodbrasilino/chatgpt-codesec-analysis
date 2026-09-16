#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int num) {
    int sum = 0;
    if (num < 0) {
        num = -num;
    }
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int* compute_sum_of_digits_list(const int* list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    int* results = (int*)malloc(size * sizeof(int));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        results[i] = sum_of_digits(list[i]);
    }

    return results;
}

int main(void) {
    int numbers[] = {123, -456, 789, 0, 42};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    int* sums = compute_sum_of_digits_list(numbers, size);
    if (sums == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("Sum of digits of %d is %d\n", numbers[i], sums[i]);
    }

    free(sums);
    sums = NULL;

    return EXIT_SUCCESS;
}