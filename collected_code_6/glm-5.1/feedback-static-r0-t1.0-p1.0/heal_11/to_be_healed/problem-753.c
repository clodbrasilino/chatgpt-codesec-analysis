#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    double val_a = ((Tuple *)a)->value;
    double val_b = ((Tuple *)b)->value;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

Tuple *find_min_k_tuples(Tuple *list, size_t list_size, size_t k, size_t *out_size) {
    if (list == NULL || out_size == NULL) {
        return NULL;
    }

    if (k == 0 || list_size == 0) {
        *out_size = 0;
        return NULL;
    }

    size_t actual_k = (k < list_size) ? k : list_size;

    if (list_size > SIZE_MAX / sizeof(Tuple)) {
        return NULL;
    }

    size_t sorted_list_size = list_size * sizeof(Tuple);
    Tuple *sorted_list = (Tuple *)malloc(sorted_list_size);
    if (sorted_list == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err = memcpy_s(sorted_list, sorted_list_size, list, sorted_list_size);
    if (err != 0) {
        free(sorted_list);
        return NULL;
    }

    qsort(sorted_list, list_size, sizeof(Tuple), compare_tuples);

    if (actual_k > SIZE_MAX / sizeof(Tuple)) {
        free(sorted_list);
        return NULL;
    }

    size_t result_size_bytes = actual_k * sizeof(Tuple);
    Tuple *result = (Tuple *)malloc(result_size_bytes);
    if (result == NULL) {
        free(sorted_list);
        return NULL;
    }

    errno_t res_err = memcpy_s(result, result_size_bytes, sorted_list, result_size_bytes);
    if (res_err != 0) {
        free(sorted_list);
        free(result);
        return NULL;
    }

    free(sorted_list);
    *out_size = actual_k;

    return result;
}

int main() {
    Tuple list[] = {
        {1, 9.8},
        {2, 2.1},
        {3, 5.5},
        /* Possible weaknesses found:
         *  'memcpy' declared here
         */
        {4, 1.2},
        {5, 7.3}
    };

    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t k = 3;
    size_t result_size = 0;

    Tuple *min_k = find_min_k_tuples(list, list_size, k, &result_size);

    if (min_k != NULL) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("ID: %d, Value: %.2f\n", min_k[i].id, min_k[i].value);
        }
        free(min_k);
    }

    return 0;
}