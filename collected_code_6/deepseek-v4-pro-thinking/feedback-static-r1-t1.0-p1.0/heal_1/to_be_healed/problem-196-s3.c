#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple *tuple_create(const int *data, size_t length) {
    if (length > 0 && data == NULL) {
        return NULL;
    }
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->data = NULL;
    tuple->length = 0;
    if (length > 0) {
        tuple->data = malloc(length * sizeof(int));
        if (tuple->data == NULL) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < length; ++i) {
            tuple->data[i] = data[i];
        }
    }
    tuple->length = length;
    return tuple;
}

void tuple_destroy(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

int remove_tuples_with_length_k(Tuple **tuples, size_t *count, size_t k) {
    if (tuples == NULL || count == NULL) {
        return -1;
    }
    if (*tuples == NULL && *count != 0) {
        return -1;
    }
    for (size_t i = 0; i < *count; ++i) {
        /* Possible weaknesses found:
         *  initializing 'Tuple *' with an expression of incompatible type 'Tuple'; take the address with &
         *  incompatible types when initializing type 'Tuple *' using type 'Tuple'
         *  Variable 'tuple' can be declared as pointer to const [constVariablePointer]
         */
        Tuple *tuple = (*tuples)[i];
        if (tuple == NULL) {
            return -1;
        }
        if (tuple->length > 0 && tuple->data == NULL) {
            return -1;
        }
    }
    size_t old_count = *count;
    size_t write = 0;
    for (size_t i = 0; i < old_count; ++i) {
        /* Possible weaknesses found:
         *  initializing 'Tuple *' with an expression of incompatible type 'Tuple'; take the address with &
         *  incompatible types when initializing type 'Tuple *' using type 'Tuple'
         */
        Tuple *tuple = (*tuples)[i];
        if (tuple->length == k) {
            tuple_destroy(tuple);
            /* Possible weaknesses found:
             *  incompatible types when assigning to type 'Tuple' from type 'void *'
             *  assigning to 'Tuple' from incompatible type 'void *'
             */
            (*tuples)[i] = NULL;
        } else {
            if (write != i) {
                /* Possible weaknesses found:
                 *  incompatible types when assigning to type 'Tuple' from type 'Tuple *'
                 *  assigning to 'Tuple' from incompatible type 'Tuple *'; dereference with *
                 */
                (*tuples)[write] = tuple;
                /* Possible weaknesses found:
                 *  incompatible types when assigning to type 'Tuple' from type 'void *'
                 *  assigning to 'Tuple' from incompatible type 'void *'
                 */
                (*tuples)[i] = NULL;
            }
            ++write;
        }
    }
    for (size_t i = write; i < old_count; ++i) {
        /* Possible weaknesses found:
         *  incompatible types when assigning to type 'Tuple' from type 'void *'
         *  assigning to 'Tuple' from incompatible type 'void *'
         */
        (*tuples)[i] = NULL;
    }
    *count = write;
    if (write == 0) {
        free(*tuples);
        *tuples = NULL;
        return 0;
    }
    Tuple **new_tuples = realloc(*tuples, write * sizeof(Tuple *));
    if (new_tuples != NULL) {
        /* Possible weaknesses found:
         *  assignment to 'Tuple *' from incompatible pointer type 'Tuple **' [-Wincompatible-pointer-types]
         */
        *tuples = new_tuples;
    }
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'a' can be declared as const array [constVariable]
     */
    int a[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 'c' can be declared as const array [constVariable]
     */
    int c[] = {6, 7, 8, 9};
    /* Possible weaknesses found:
     *  Variable 'd' can be declared as const array [constVariable]
     */
    int d[] = {10};
    size_t count = 4;
    Tuple **tuples = malloc(count * sizeof(Tuple *));
    if (tuples == NULL) {
        return 1;
    }
    tuples[0] = tuple_create(a, 3);
    tuples[1] = tuple_create(b, 2);
    tuples[2] = tuple_create(c, 4);
    tuples[3] = tuple_create(d, 1);
    for (size_t i = 0; i < count; ++i) {
        if (tuples[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                tuple_destroy(tuples[j]);
            }
            free(tuples);
            return 1;
        }
    }
    if (remove_tuples_with_length_k(tuples, &count, 2) != 0) {
        for (size_t i = 0; i < count; ++i) {
            tuple_destroy(tuples[i]);
        }
        free(tuples);
        return 1;
    }
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < tuples[i]->length; ++j) {
            printf("%d ", tuples[i]->data[j]);
        }
        printf("\n");
    }
    for (size_t i = 0; i < count; ++i) {
        tuple_destroy(tuples[i]);
    }
    free(tuples);
    return 0;
}