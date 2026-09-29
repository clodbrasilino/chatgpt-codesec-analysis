#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int* get_n_smallest(const int *data, size_t data_size, size_t n, size_t *result_size) {
    if (data == NULL || result_size == NULL || data_size == 0 || n == 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }
    
    if (data_size > SIZE_MAX / sizeof(int)) {
        *result_size = 0;
        return NULL;
    }
    
    size_t actual_n = (n < data_size) ? n : data_size;
    
    if (actual_n > SIZE_MAX / sizeof(int)) {
        *result_size = 0;
        return NULL;
    }
    
    int *temp = malloc(data_size * sizeof(int));
    if (temp == NULL) {
        *result_size = 0;
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  'copy_size' is assigned value 'data_size*sizeof(int)' here.
     */
    size_t copy_size = data_size * sizeof(int);
    /* Possible weaknesses found:
     *  The comparison 'copy_size > data_size*sizeof(int)' is always false because 'copy_size' and 'data_size*sizeof(int)' represent the same value.
     *  The comparison 'copy_size > data_size*sizeof(int)' is always false because 'copy_size' and 'data_size*sizeof(int)' represent the same value. [knownConditionTrueFalse]
     */
    if (copy_size > data_size * sizeof(int)) {
        free(temp);
        *result_size = 0;
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, data, copy_size);
    qsort(temp, data_size, sizeof(int), compare_ints);
    
    int *result = malloc(actual_n * sizeof(int));
    if (result == NULL) {
        free(temp);
        *result_size = 0;
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  'result_copy_size' is assigned value 'actual_n*sizeof(int)' here.
     */
    size_t result_copy_size = actual_n * sizeof(int);
    /* Possible weaknesses found:
     *  The comparison 'result_copy_size > actual_n*sizeof(int)' is always false because 'result_copy_size' and 'actual_n*sizeof(int)' represent the same value. [knownConditionTrueFalse]
     *  The comparison 'result_copy_size > actual_n*sizeof(int)' is always false because 'result_copy_size' and 'actual_n*sizeof(int)' represent the same value.
     */
    if (result_copy_size > actual_n * sizeof(int)) {
        free(temp);
        free(result);
        *result_size = 0;
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, temp, result_copy_size);
    free(temp);
    *result_size = actual_n;
    return result;
}

int main(void) {
    int dataset[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;
    
    int *smallest = get_n_smallest(dataset, dataset_size, n, &result_size);
    
    if (smallest == NULL) {
        fprintf(stderr, "Error: Failed to retrieve smallest items\n");
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