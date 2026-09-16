#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'indices' can be declared as const array [constParameter]
 */
void* elementwise_extract(const void* t1, const void* t2, size_t tuple_size, size_t elem_size, size_t indices[], size_t num_indices, void** out_tuple) {
    if (tuple_size == 0 || elem_size == 0) {
        return NULL;
    }

    void* elementwise = malloc(num_indices * elem_size);
    if (elementwise == NULL) {
        return NULL;
    }

    *out_tuple = malloc(tuple_size * elem_size);
    if (*out_tuple == NULL) {
        free(elementwise);
        return NULL;
    }

    for (size_t i = 0; i < tuple_size; i++) {
        memcpy((char*)*out_tuple + i * elem_size, (const char*)t1 + i * elem_size, elem_size);
        memcpy((char*)*out_tuple + i * elem_size, (const char*)t2 + i * elem_size, elem_size);
    }

    for (size_t i = 0; i < num_indices; i++) {
        size_t idx = indices[i];
        if (idx < tuple_size) {
            memcpy((char*)elementwise + i * elem_size, (const char*)t1 + idx * elem_size, elem_size);
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
    /* Possible weaknesses found:
     *  Variable 'a' can be declared as const array [constVariable]
     */
    int a[] = {1, 2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {5, 6, 7, 8};
    size_t idx[] = {1, 3};
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

    /* Possible weaknesses found:
     *  Variable 't' can be declared as pointer to const [constVariablePointer]
     */
    int* t = (int*)out_tuple;
    for (size_t i = 0; i < 4; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");

    free(elementwise);
    free(out_tuple);

    return 0;
}