#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple* create_tuple(size_t length) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    tuple->data = (int*)malloc(length * sizeof(int));
    tuple->length = length;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    free(tuple->data);
    free(tuple);
}

Tuple* remove_matching_tuples(const Tuple *tuple1, const Tuple *tuple2) {
    size_t new_length = 0;
    for (size_t i = 0; i < tuple1->length; ++i) {
        /* Possible weaknesses found:
         *  call to undeclared function 'is_in_tuple'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'is_in_tuple' [-Wimplicit-function-declaration]
         */
        if (tuple2->length == 0 || !is_in_tuple(tuple2, tuple1->data[i])) {
            ++new_length;
        }
    }

    Tuple *result = create_tuple(new_length);
    size_t index = 0;
    for (size_t i = 0; i < tuple1->length; ++i) {
        /* Possible weaknesses found:
         *  call to undeclared function 'is_in_tuple'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        if (tuple2->length == 0 || !is_in_tuple(tuple2, tuple1->data[i])) {
            result->data[index++] = tuple1->data[i];
        }
    }

    return result;
}

int is_in_tuple(const Tuple *tuple, int value) {
    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Tuple *tuple1 = create_tuple(5);
    tuple1->data[0] = 1;
    tuple1->data[1] = 2;
    tuple1->data[2] = 3;
    tuple1->data[3] = 4;
    tuple1->data[4] = 5;

    Tuple *tuple2 = create_tuple(3);
    tuple2->data[0] = 2;
    tuple2->data[1] = 4;
    tuple2->data[2] = 6;

    Tuple *result = remove_matching_tuples(tuple1, tuple2);

    for (size_t i = 0; i < result->length; ++i) {
        printf("%d ", result->data[i]);
    }
    printf("\n");

    free_tuple(tuple1);
    free_tuple(tuple2);
    free_tuple(result);

    return 0;
}