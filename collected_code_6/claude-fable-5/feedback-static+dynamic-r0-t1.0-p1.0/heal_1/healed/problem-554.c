#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *arr, size_t size, size_t *odd_count)
{
    size_t count = 0;
    int *result = NULL;

    if (arr == NULL || odd_count == NULL || size == 0) {
        if (odd_count != NULL) {
            *odd_count = 0;
        }
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    *odd_count = count;

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        *odd_count = 0;
        return NULL;
    }

    count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[count] = arr[i];
            count++;
        }
    }

    return result;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -3, -4};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;
    int *odds;

    odds = find_odd_numbers(numbers, size, &odd_count);

    if (odds == NULL && odd_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (odd_count == 0) {
        printf("No odd numbers found\n");
    } else {
        printf("Odd numbers: ");
        for (size_t i = 0; i < odd_count; i++) {
            printf("%d ", odds[i]);
        }
        printf("\n");
    }

    free(odds);

    return EXIT_SUCCESS;
}