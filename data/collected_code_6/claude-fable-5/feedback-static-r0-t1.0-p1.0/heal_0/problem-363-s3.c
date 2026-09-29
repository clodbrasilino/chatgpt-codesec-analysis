#include <stdio.h>
#include <stdlib.h>

int add_k_to_elements(const int *input, int *output, size_t size, int k)
{
    size_t i;

    if (input == NULL || output == NULL || size == 0U) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        long long sum = (long long)input[i] + (long long)k;
        if (sum > 2147483647LL || sum < -2147483648LL) {
            return -1;
        }
        output[i] = (int)sum;
    }

    return 0;
}

int main(void)
{
    int tuple[] = {1, 3, 4, 5, 6, 8};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int k = 4;
    int *result;
    size_t i;

    result = malloc(size * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (add_k_to_elements(tuple, result, size, k) != 0) {
        fprintf(stderr, "Failed to add k to elements\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    for (i = 0U; i < size; i++) {
        printf("%d ", tuple[i]);
    }
    printf("\n");

    printf("Result tuple:   ");
    for (i = 0U; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}