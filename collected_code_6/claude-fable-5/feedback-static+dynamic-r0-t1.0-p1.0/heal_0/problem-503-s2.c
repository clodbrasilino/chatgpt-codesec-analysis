#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int add_consecutive(const int *input, size_t input_len, int **output, size_t *output_len)
{
    size_t i;
    int *result;

    if (input == NULL || output == NULL || output_len == NULL) {
        return -1;
    }

    if (input_len < 2) {
        *output = NULL;
        *output_len = 0;
        return -1;
    }

    result = malloc((input_len - 1) * sizeof(int));
    if (result == NULL) {
        *output = NULL;
        *output_len = 0;
        return -1;
    }

    for (i = 0; i < input_len - 1; i++) {
        long long sum = (long long)input[i] + (long long)input[i + 1];
        if (sum > INT_MAX || sum < INT_MIN) {
            free(result);
            *output = NULL;
            *output_len = 0;
            return -1;
        }
        result[i] = (int)sum;
    }

    *output = result;
    *output_len = input_len - 1;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    size_t numbers_len = sizeof(numbers) / sizeof(numbers[0]);
    int *sums = NULL;
    size_t sums_len = 0;
    size_t i;

    if (add_consecutive(numbers, numbers_len, &sums, &sums_len) != 0) {
        fprintf(stderr, "Failed to compute consecutive sums\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < sums_len; i++) {
        if (printf("%d\n", sums[i]) < 0) {
            free(sums);
            return EXIT_FAILURE;
        }
    }

    free(sums);
    return EXIT_SUCCESS;
}