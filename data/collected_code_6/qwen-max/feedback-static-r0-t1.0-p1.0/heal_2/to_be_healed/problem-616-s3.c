#include <stdio.h>
#include <stdlib.h>

void tuple_modulo(const int *tuple1, const int *tuple2, int *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (tuple2[i] != 0) {
            result[i] = tuple1[i] % tuple2[i];
        } else {
            result[i] = 0;
        }
    }
}

int main() {
    int tuple1[] = {10, 20, 30};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = {3, 5, 0};
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result = malloc(length * sizeof(int));
    if (result == NULL) {
        return 1;
    }
    tuple_modulo(tuple1, tuple2, result, length);
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}