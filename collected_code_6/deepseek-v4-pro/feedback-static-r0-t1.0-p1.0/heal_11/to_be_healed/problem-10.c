#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int *get_n_smallest(const int *data, size_t data_size, size_t n, size_t *result_size) {
    int *copy = NULL;
    int *result = NULL;
    size_t total_bytes;
    size_t result_bytes;

    if (data == NULL || result_size == NULL || n == 0 || data_size == 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (n > data_size) {
        n = data_size;
    }

    if (data_size > SIZE_MAX / sizeof(int)) {
        *result_size = 0;
        return NULL;
    }
    total_bytes = data_size * sizeof(int);

    /* Possible weaknesses found:
     *  Assuming that condition 'total_bytes==0' is not redundant
     */
    if (total_bytes == 0) {
        *result_size = 0;
        return NULL;
    }

    copy = malloc(total_bytes);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        *result_size = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'total_bytes>0' is always true
     *  Condition 'total_bytes>0' is always true [knownConditionTrueFalse]
     */
    if (data_size <= (SIZE_MAX / sizeof(int)) && total_bytes > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, data, total_bytes);
    } else {
        free(copy);
        *result_size = 0;
        return NULL;
    }

    qsort(copy, data_size, sizeof(int), compare_ints);

    if (n > SIZE_MAX / sizeof(int)) {
        free(copy);
        *result_size = 0;
        return NULL;
    }
    result_bytes = n * sizeof(int);

    /* Possible weaknesses found:
     *  Assuming that condition 'result_bytes==0' is not redundant
     */
    if (result_bytes == 0) {
        free(copy);
        *result_size = 0;
        return NULL;
    }

    result = malloc(result_bytes);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        free(copy);
        *result_size = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'result_bytes>0' is always true
     *  Condition 'result_bytes>0' is always true [knownConditionTrueFalse]
     */
    if (n <= (SIZE_MAX / sizeof(int)) && result_bytes > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, copy, result_bytes);
    } else {
        free(copy);
        free(result);
        *result_size = 0;
        return NULL;
    }

    free(copy);
    *result_size = n;
    return result;
}

int main(void) {
    int dataset[] = {42, 17, 8, 3, 99, 23, 56, 1, 74, 12};
    size_t data_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;
    int *smallest = NULL;

    smallest = get_n_smallest(dataset, data_size, n, &result_size);

    if (smallest != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", smallest[i]);
        }
        printf("\n");
        free(smallest);
    } else {
        printf("No result\n");
    }

    return 0;
}