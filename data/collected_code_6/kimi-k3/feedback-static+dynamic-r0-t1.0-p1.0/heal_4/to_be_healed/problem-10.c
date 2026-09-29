#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int* get_n_smallest(const int *data, size_t data_size, size_t n, size_t *result_size) {
    if (data == NULL || result_size == NULL || data_size == 0 || n == 0) {
        if (result_size != NULL) *result_size = 0;
        return NULL;
    }
    
    size_t count = (n < data_size) ? n : data_size;
    
    if (count > SIZE_MAX / sizeof(int)) {
        *result_size = 0;
        return NULL;
    }
    
    size_t alloc_size = count * sizeof(int);
    int *result = malloc(alloc_size);
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }
    
    if (alloc_size > 0 && data_size >= count) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, data, alloc_size);
    } else {
        free(result);
        *result_size = 0;
        return NULL;
    }
    
    qsort(result, count, sizeof(int), compare_ints);
    *result_size = count;
    return result;
}

int main(void) {
    int dataset[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    size_t data_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;
    
    int *smallest = get_n_smallest(dataset, data_size, n, &result_size);
    if (smallest == NULL) {
        fprintf(stderr, "Error: Failed to get smallest items\n");
        return EXIT_FAILURE;
    }
    
    printf("The %zu smallest items are: ", result_size);
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");
    
    free(smallest);
    return EXIT_SUCCESS;
}