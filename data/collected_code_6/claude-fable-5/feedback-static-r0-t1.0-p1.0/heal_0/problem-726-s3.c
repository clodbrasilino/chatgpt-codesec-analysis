#include <stdio.h>
#include <stdlib.h>

int multiply_adjacent(const int *input, size_t input_len, long long *output, size_t output_len)
{
    size_t i;

    if (input == NULL || output == NULL) {
        return -1;
    }

    if (input_len < 2U || output_len < (input_len - 1U)) {
        return -1;
    }

    for (i = 0U; i < input_len - 1U; i++) {
        output[i] = (long long)input[i] * (long long)input[i + 1U];
    }

    return 0;
}

int main(void)
{
    int tuple[] = {1, 5, 7, 8, 10};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    long long *result;
    size_t result_len;
    size_t i;

    if (tuple_len < 2U) {
        fprintf(stderr, "Tuple must contain at least two elements\n");
        return EXIT_FAILURE;
    }

    result_len = tuple_len - 1U;

    result = (long long *)malloc(result_len * sizeof(long long));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (multiply_adjacent(tuple, tuple_len, result, result_len) != 0) {
        fprintf(stderr, "Failed to multiply adjacent elements\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0U; i < result_len; i++) {
        printf("%lld", result[i]);
        if (i < result_len - 1U) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}