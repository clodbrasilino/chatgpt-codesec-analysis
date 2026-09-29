#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int id;
    double value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    double val_a = ((const Tuple *)a)->value;
    double val_b = ((const Tuple *)b)->value;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

Tuple *find_min_k_tuples(Tuple *tuples, size_t tuple_count, size_t k, size_t *out_count) {
    if (out_count == NULL) {
        return NULL;
    }
    
    if (tuples == NULL || tuple_count == 0 || k == 0) {
        *out_count = 0;
        return NULL;
    }

    size_t actual_k = k < tuple_count ? k : tuple_count;
    
    if (tuple_count > SIZE_MAX / sizeof(Tuple) || actual_k > SIZE_MAX / sizeof(Tuple)) {
        *out_count = 0;
        return NULL;
    }

    size_t sorted_size = tuple_count * sizeof(Tuple);
    Tuple *sorted = malloc(sorted_size);
    if (sorted == NULL) {
        *out_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, tuples, sorted_size);
    qsort(sorted, tuple_count, sizeof(Tuple), compare_tuples);

    size_t result_size = actual_k * sizeof(Tuple);
    Tuple *result = malloc(result_size);
    if (result == NULL) {
        free(sorted);
        *out_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, sorted, result_size);
    free(sorted);
    
    *out_count = actual_k;
    return result;
}

int main() {
    Tuple data[] = {
        {1, 9.8},
        {2, 2.5},
        {3, 7.1},
        {4, 1.2},
        {5, 5.6}
    };
    
    size_t data_count = sizeof(data) / sizeof(data[0]);
    size_t k = 3;
    size_t result_count = 0;
    
    Tuple *min_k = find_min_k_tuples(data, data_count, k, &result_count);
    
    if (min_k != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("ID: %d, Value: %.2f\n", min_k[i].id, min_k[i].value);
        }
        free(min_k);
    }
    
    return 0;
}