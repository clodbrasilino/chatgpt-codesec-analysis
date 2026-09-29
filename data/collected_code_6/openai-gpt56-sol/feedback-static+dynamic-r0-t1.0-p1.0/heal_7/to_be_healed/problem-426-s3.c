#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  */

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size)
{
    if (output_size == NULL) {
        return NULL;
    }

    *output_size = 0;

    if (input == NULL || input_size == 0) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < input_size; ++i) {
        if (input[i] % 2 != 0) {
            ++count;
        }
    }

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *output = malloc(count * sizeof(*output));
    if (output == NULL) {
        return NULL;
    }

    size_t output_index = 0;

    for (size_t i = 0; i < input_size; ++i) {
        if (input[i] % 2 != 0) {
            output[output_index++] = input[i];
        }
    }

    *output_size = output_index;
    return output;
}

int main(void)
{
    size_t input_size = 0;

    if (scanf("%zu", &input_size) != 1) {
        return EXIT_FAILURE;
    }

    if (input_size > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *input = NULL;

    if (input_size != 0) {
        input = malloc(input_size * sizeof(*input));
        if (input == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < input_size; ++i) {
            if (scanf("%d", &input[i]) != 1) {
                free(input);
                return EXIT_FAILURE;
            }
        }
    }

    size_t output_size = 0;
    int *output = filter_odd_numbers(input, input_size, &output_size);

    free(input);

    if (input_size != 0 && output == NULL && output_size != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_size; ++i) {
        if (i != 0) {
            printf(" ");
        }

        printf("%d", output[i]);
    }

    if (output_size != 0) {
        printf("\n");
    }

    free(output);
    return EXIT_SUCCESS;
}