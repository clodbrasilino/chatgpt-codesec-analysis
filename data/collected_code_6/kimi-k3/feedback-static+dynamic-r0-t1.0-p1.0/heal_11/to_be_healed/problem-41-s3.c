#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [8, 6, 4], got <no output>
  *  test case 0 failed: expected [2, 4, 6, 8, 10], got <no output>
  *  test case 1 failed: expected [10, 20, 84], got <no output>
  */

int *filter_even_numbers(const int *input_array, size_t array_size, size_t *result_size)
{
    int *even_numbers;
    size_t i;
    size_t even_count;

    if (input_array == NULL || result_size == NULL) {
        return NULL;
    }

    if (array_size == 0) {
        *result_size = 0;
        return NULL;
    }

    if (array_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    even_numbers = (int *)malloc(array_size * sizeof(int));
    if (even_numbers == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    even_count = 0;
    for (i = 0; i < array_size; i++) {
        if (input_array[i] % 2 == 0) {
            even_numbers[even_count] = input_array[i];
            even_count++;
        }
    }

    *result_size = even_count;
    return even_numbers;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t array_size = sizeof(numbers) / sizeof(numbers[0]);
    size_t even_count = 0;
    int *even_numbers;
    size_t i;

    errno = 0;
    even_numbers = filter_even_numbers(numbers, array_size, &even_count);

    if (even_numbers == NULL) {
        if (errno == ENOMEM) {
            fprintf(stderr, "Error: Failed to allocate memory\n");
        } else {
            fprintf(stderr, "Error: Invalid input\n");
        }
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0; i < even_count; i++) {
        printf("%d", even_numbers[i]);
        if (i < even_count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(even_numbers);
    even_numbers = NULL;

    return EXIT_SUCCESS;
}