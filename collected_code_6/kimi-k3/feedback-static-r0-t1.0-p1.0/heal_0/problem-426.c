#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *arr, size_t size, size_t *result_size) {
    if (arr == NULL || result_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[index++] = arr[i];
        }
    }

    *result_size = count;
    return result;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t result_size = 0;

    int *odd_numbers = filter_odd_numbers(numbers, size, &result_size);
    if (odd_numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Odd numbers: ");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    free(odd_numbers);
    return EXIT_SUCCESS;
}