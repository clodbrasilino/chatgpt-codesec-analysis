#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* elementwise_extract(const void* t1, const void* t2, size_t tuple_size, size_t elem_size, const size_t indices[], size_t num_indices, void** out_tuple) {
    if (tuple_size == 0 || elem_size == 0 || t1 == NULL || t2 == NULL || indices == NULL || out_tuple == NULL) {
        return NULL;
    }

    size_t required_elementwise_size = num_indices * elem_size;
    if (required_elementwise_size / elem_size != num_indices) {
        return NULL;
    }

    size_t required_tuple_size = tuple_size * elem_size;
    if (required_tuple_size / elem_size != tuple_size) {
        return NULL;
    }

    void* elementwise = malloc(required_elementwise_size);
    if (elementwise == NULL) {
        return NULL;
    }

    *out_tuple = malloc(required_tuple_size);
    if (*out_tuple == NULL) {
        free(elementwise);
        return NULL;
    }

    if (required_tuple_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*out_tuple, t2, required_tuple_size);
    }

    for (size_t i = 0; i < num_indices; i++) {
        size_t idx = indices[i];
        if (idx < tuple_size) {
            if (elem_size > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy((char*)elementwise + i * elem_size, (const char*)t1 + idx * elem_size, elem_size);
            }
        } else {
            free(elementwise);
            free(*out_tuple);
            *out_tuple = NULL;
            return NULL;
        }
    }

    return elementwise;
}

int main() {
    const int a[] = {1, 2, 3, 4};
    const int b[] = {5, 6, 7, 8};
    const size_t idx[] = {1, 3};
    void* out_tuple = NULL;

    int* elementwise = (int*)elementwise_extract(a, b, 4, sizeof(int), idx, 2, &out_tuple);
    if (elementwise == NULL || out_tuple == NULL) {
        if (elementwise) free(elementwise);
        if (out_tuple) free(out_tuple);
        return 1;
    }

    for (size_t i = 0; i < 2; i++) {
        printf("%d ", elementwise[i]);
    }
    printf("\n");

    const int* t = (const int*)out_tuple;
    for (size_t i = 0; i < 4; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");

    free(elementwise);
    free(out_tuple);

    return 0;
}