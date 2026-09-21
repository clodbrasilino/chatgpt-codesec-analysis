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
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err1 = memcpy_s(sorted, sorted_size, tuples, sorted_size);
    if (err1 != 0) {
        free(sorted);
        *out_count = 0;
        return NULL;
    }

    qsort(sorted, tuple_count, sizeof(Tuple), compare_tuples);

    size_t result_size = actual_k * sizeof(Tuple);
    Tuple *result = malloc(result_size);
    if (result == NULL) {
        free(sorted);
        *out_count = 0;
        return NULL;
    }

    errno_t err2 = memcpy_s(result, result_size, sorted, result_size);
    if (err2 != 0) {
        free(sorted);
        free(result);
        *out_count = 0;
        return NULL;
    }

    free(sorted);
    
    *out_count = actual_k;
    return result;
}

int main() {
    Tuple data[] = {
        {1, 9.8},
        {2, 2.5},
        /* Possible weaknesses found:
         *  'memcpy' declared here
         */
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