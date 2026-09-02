#include <stdio.h>
#include <stdlib.h>

int sum_array(const int *arr, size_t size, long long *result) {
    if (arr == NULL || result == NULL) {
        return -1;
    }
    if (size == 0) {
        *result = 0;
        return 0;
    }
    long long sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    *result = sum;
    return 0;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long total = 0;

    if (sum_array(numbers, count, &total) == 0) {
        printf("Sum: %lld\n", total);
    } else {
        fprintf(stderr, "Error: invalid input to sum_array\n");
        return EXIT_FAILURE;
    }

    int ret = sum_array(NULL, count, &total);
    if (ret != 0) {
        fprintf(stderr, "Error: invalid input to sum_array\n");
        return EXIT_FAILURE;
    }

    if (sum_array(numbers, 0, &total) == 0) {
        printf("Empty array sum: %lld\n", total);
    }

    return EXIT_SUCCESS;
}