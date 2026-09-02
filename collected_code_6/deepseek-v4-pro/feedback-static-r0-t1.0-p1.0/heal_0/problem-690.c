#include <stdio.h>
#include <stdlib.h>

int multiply_consecutive(const int *numbers, size_t length, int **results, size_t *result_count) {
    if (numbers == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    if (length < 2) {
        *results = NULL;
        *result_count = 0;
        return 0;
    }

    int *temp_results = (int *)malloc((length - 1) * sizeof(int));
    if (temp_results == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length - 1; i++) {
        temp_results[i] = numbers[i] * numbers[i + 1];
    }

    *results = temp_results;
    *result_count = length - 1;
    return 0;
}

int main(void) {
    int numbers[] = {2, 3, 5, 7, 11, 13};
    int *products = NULL;
    size_t product_count = 0;

    if (multiply_consecutive(numbers, sizeof(numbers) / sizeof(numbers[0]), &products, &product_count) != 0) {
        fprintf(stderr, "Error processing numbers\n");
        return 1;
    }

    printf("Products of consecutive numbers:\n");
    for (size_t i = 0; i < product_count; i++) {
        printf("%d ", products[i]);
    }
    printf("\n");

    free(products);
    products = NULL;

    return 0;
}