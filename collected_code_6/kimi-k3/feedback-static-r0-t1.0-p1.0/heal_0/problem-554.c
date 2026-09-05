#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *arr, size_t size, size_t *odd_count) {
    if (arr == NULL || odd_count == NULL) {
        return NULL;
    }

    *odd_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            (*odd_count)++;
        }
    }

    if (*odd_count == 0) {
        return NULL;
    }

    int *odd_numbers = malloc(*odd_count * sizeof(int));
    if (odd_numbers == NULL) {
        *odd_count = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            odd_numbers[index] = arr[i];
            index++;
        }
    }

    return odd_numbers;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;

    int *odd_numbers = find_odd_numbers(numbers, size, &odd_count);

    if (odd_numbers == NULL) {
        if (odd_count == 0) {
            printf("No odd numbers found.\n");
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    } else {
        printf("Odd numbers: ");
        for (size_t i = 0; i < odd_count; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
    }

    return EXIT_SUCCESS;
}