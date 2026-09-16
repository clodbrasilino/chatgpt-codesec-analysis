#include <stdio.h>
#include <stdlib.h>

int *find_odd_numbers(const int *arr, size_t size, size_t *odd_count)
{
    size_t count = 0;
    size_t i;
    int *result = NULL;
    size_t idx = 0;

    if (arr == NULL || odd_count == NULL) {
        return NULL;
    }

    *odd_count = 0;

    for (i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[idx] = arr[i];
            idx++;
        }
    }

    *odd_count = count;
    return result;
}

int main(void)
{
    int numbers[] = { 12, 7, 4, 9, 20, 15, 8, 3, 6, 11 };
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;
    size_t i;
    int *odds = NULL;

    odds = find_odd_numbers(numbers, size, &odd_count);

    if (odds == NULL) {
        if (odd_count == 0) {
            if (printf("No odd numbers found.\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Odd numbers: ") < 0) {
        free(odds);
        return EXIT_FAILURE;
    }

    for (i = 0; i < odd_count; i++) {
        if (printf("%d ", odds[i]) < 0) {
            free(odds);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(odds);
        return EXIT_FAILURE;
    }

    free(odds);
    odds = NULL;

    return EXIT_SUCCESS;
}