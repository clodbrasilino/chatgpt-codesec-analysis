#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
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
    
    if (tuples == NULL || tuple_count == 0) {
        *out_count = 0;
        return NULL;
    }
    
    size_t actual_k = k < tuple_count ? k : tuple_count;
    
    Tuple *sorted = (Tuple *)malloc(tuple_count * sizeof(Tuple));
    if (sorted == NULL) {
        *out_count = 0;
        return NULL;
    }
    
    memcpy(sorted, tuples, tuple_count * sizeof(Tuple));
    
    qsort(sorted, tuple_count, sizeof(Tuple), compare_tuples);
    
    Tuple *result = (Tuple *)malloc(actual_k * sizeof(Tuple));
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
    Tuple tuples[] = {
        {1, "alpha", 9.8},
        {2, "beta", 3.14},
        {3, "gamma", 8.1},
        {4, "delta", 1.61},
        {5, "epsilon", 5.5}
    };
    
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t k = 3;
    size_t out_count = 0;
    
    Tuple *min_k = find_min_k_tuples(tuples, tuple_count, k, &out_count);
    
    if (min_k != NULL) {
        for (size_t i = 0; i < out_count; ++i) {
            printf("ID: %d, Name: %s, Value: %.2f\n", min_k[i].id, min_k[i].name, min_k[i].value);
        }
        free(min_k);
    }
    
    return 0;
}