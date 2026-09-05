#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    Tuple *sorted = malloc(tuple_count * sizeof(Tuple));
    if (sorted == NULL) {
        *out_count = 0;
        return NULL;
    }

    memcpy(sorted, tuples, tuple_count * sizeof(Tuple));
    qsort(sorted, tuple_count, sizeof(Tuple), compare_tuples);

    Tuple *result = malloc(actual_k * sizeof(Tuple));
    if (result == NULL) {
        free(sorted);
        *out_count = 0;
        return NULL;
    }

    memcpy(result, sorted, actual_k * sizeof(Tuple));
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