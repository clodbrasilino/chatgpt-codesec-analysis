#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size)
{
    if (output_size == NULL) {
        return NULL;
    }

    *output_size = 0;

    if (input_size == 0) {
        return NULL;
    }

    if (input == NULL) {
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

    size_t index = 0;

    for (size_t i = 0; i < input_size; ++i) {
        if (input[i] % 2 != 0) {
            output[index++] = input[i];
        }
    }

    *output_size = count;
    return output;
}

int main(void)
{
    size_t input_size;

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

    printf("[");

    for (size_t i = 0; i < output_size; ++i) {
        printf("%s%d", i == 0 ? "" : ", ", output[i]);
    }

    printf("]\n");

    free(output);
    return EXIT_SUCCESS;
}