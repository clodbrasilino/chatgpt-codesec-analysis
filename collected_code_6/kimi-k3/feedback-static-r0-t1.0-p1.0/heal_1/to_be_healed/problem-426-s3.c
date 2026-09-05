#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int filter_odd(const int *input, size_t count, int **output, size_t *output_count)
{
    size_t i;
    size_t odd_count = 0;
    int *result;

    if (input == NULL || output == NULL || output_count == NULL) {
        return -1;
    }

    if (count == 0) {
        *output = NULL;
        *output_count = 0;
        return 0;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (input[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0) {
        *output = NULL;
        *output_count = 0;
        return 0;
    }

    result = malloc(odd_count * sizeof(int));
    if (result == NULL) {
        return -1;
    }

    odd_count = 0;
    for (i = 0; i < count; i++) {
        if (input[i] % 2 != 0) {
            result[odd_count] = input[i];
            odd_count++;
        }
    }

    *output = result;
    *output_count = odd_count;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int *odd_numbers = NULL;
    size_t odd_count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    int status;

    status = filter_odd(numbers, count, &odd_numbers, &odd_count);
    if (status != 0) {
        fprintf(stderr, "Error: Failed to filter odd numbers\n");
        return EXIT_FAILURE;
    }

    if (odd_count > 0 && odd_numbers != NULL) {
        printf("Odd numbers: ");
        for (i = 0; i < odd_count; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
        odd_numbers = NULL;
    } else {
        printf("No odd numbers found\n");
    }

    return EXIT_SUCCESS;
}