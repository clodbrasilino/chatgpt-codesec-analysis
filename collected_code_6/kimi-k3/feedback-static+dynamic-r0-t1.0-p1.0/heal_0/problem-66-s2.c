#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int count_positive(const int *arr, size_t size)
{
    int count;
    size_t i;

    if (arr == NULL) {
        return -1;
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] > 0) {
            if (count == INT_MAX) {
                return -1;
            }
            count++;
        }
    }

    return count;
}

int main(void)
{
    int *numbers;
    size_t count;
    size_t i;
    int result;
    long input_value;
    char *endptr;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Error: Invalid input for element count\n");
        return EXIT_FAILURE;
    }

    if (count == 0) {
        fprintf(stderr, "Error: Count must be greater than zero\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Error: Count too large\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers:\n", count);
    for (i = 0; i < count; i++) {
        if (scanf("%ld", &input_value) != 1) {
            fprintf(stderr, "Error: Invalid input for element %zu\n", i + 1);
            free(numbers);
            numbers = NULL;
            return EXIT_FAILURE;
        }

        if (input_value > INT_MAX || input_value < INT_MIN) {
            fprintf(stderr, "Error: Value out of range for element %zu\n", i + 1);
            free(numbers);
            numbers = NULL;
            return EXIT_FAILURE;
        }

        numbers[i] = (int)input_value;
    }

    result = count_positive(numbers, count);
    if (result < 0) {
        fprintf(stderr, "Error: Failed to count positive numbers\n");
        free(numbers);
        numbers = NULL;
        return EXIT_FAILURE;
    }

    printf("Number of positive numbers: %d\n", result);

    free(numbers);
    numbers = NULL;

    return EXIT_SUCCESS;
}