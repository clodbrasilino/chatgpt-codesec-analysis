#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  */

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size)
{
    int *result = NULL;
    size_t count = 0;
    size_t i;

    if (input == NULL || output_size == NULL || input_size == 0) {
        if (output_size != NULL) {
            *output_size = 0;
        }
        return NULL;
    }

    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            count++;
        }
    }

    if (count == 0) {
        *output_size = 0;
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        *output_size = 0;
        return NULL;
    }

    count = 0;
    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            result[count] = input[i];
            count++;
        }
    }

    *output_size = count;
    return result;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t numbers_size = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;
    size_t i;
    int *odd_numbers;

    odd_numbers = filter_odd_numbers(numbers, numbers_size, &odd_count);

    if (odd_numbers == NULL) {
        if (odd_count == 0) {
            printf("No odd numbers found or allocation failed.\n");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    printf("Odd numbers: ");
    for (i = 0; i < odd_count; i++) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    free(odd_numbers);
    odd_numbers = NULL;

    return EXIT_SUCCESS;
}