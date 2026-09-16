#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int *find_even_numbers(const int *input_array, size_t count, size_t *output_count)
{
    int *result = NULL;
    int *temp = NULL;
    size_t evens_found = 0;
    size_t i = 0;

    if (input_array == NULL || output_count == NULL) {
        return NULL;
    }

    *output_count = 0;

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (input_array[i] % 2 == 0) {
            result[evens_found] = input_array[i];
            evens_found++;
        }
    }

    if (evens_found == 0) {
        free(result);
        return NULL;
    }

    if (evens_found < count) {
        temp = realloc(result, evens_found * sizeof(int));
        if (temp != NULL) {
            result = temp;
        }
    }

    *output_count = evens_found;
    return result;
}

int main(void)
{
    int mixed_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -3, -4, 0};
    size_t list_size = sizeof(mixed_list) / sizeof(mixed_list[0]);
    size_t even_count = 0;
    size_t i = 0;
    int *even_numbers = NULL;

    even_numbers = find_even_numbers(mixed_list, list_size, &even_count);

    if (even_numbers == NULL) {
        if (even_count == 0) {
            fprintf(stderr, "No even numbers found or invalid input\n");
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Even numbers found: ");
    for (i = 0; i < even_count; i++) {
        printf("%d ", even_numbers[i]);
    }
    printf("\n");

    free(even_numbers);
    even_numbers = NULL;

    return EXIT_SUCCESS;
}