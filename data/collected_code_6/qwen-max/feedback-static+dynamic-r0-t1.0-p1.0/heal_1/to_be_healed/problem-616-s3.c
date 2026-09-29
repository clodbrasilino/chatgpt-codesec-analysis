#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuple1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'tuple2' can be declared as pointer to const [constParameterPointer]
 */
void tuple_modulo(int *tuple1, int *tuple2, int *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (tuple2[i] != 0) {
            result[i] = tuple1[i] % tuple2[i];
        } else {
            result[i] = 0; // Avoid division by zero
        }
    }
}

int main() {
    int tuple1[] = {10, 20, 30};
    int tuple2[] = {3, 5, 0};
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result = malloc(length * sizeof(int));
    if (result == NULL) {
        return 1; // Exit on memory allocation failure
    }
    tuple_modulo(tuple1, tuple2, result, length);
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}