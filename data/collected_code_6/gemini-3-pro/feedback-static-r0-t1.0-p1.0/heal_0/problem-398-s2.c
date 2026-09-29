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

int* compute_sum_of_digits(const int* list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    int* sums = (int*)malloc(size * sizeof(int));
    if (sums == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        sums[i] = sum_of_digits(list[i]);
    }

    return sums;
}

int main(void) {
    int numbers[] = {123, -456, 789, 0, 42};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    int* sums = compute_sum_of_digits(numbers, size);
    if (sums == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", sums[i]);
    }
    printf("\n");

    free(sums);

    return EXIT_SUCCESS;
}