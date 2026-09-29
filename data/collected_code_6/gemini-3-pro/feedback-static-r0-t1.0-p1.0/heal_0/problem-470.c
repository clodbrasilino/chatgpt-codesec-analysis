#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple* pairwise_addition(const Tuple* tuple1, const Tuple* tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->x = tuple1->x + tuple2->x;
    result->y = tuple1->y + tuple2->y;

    return result;
}

int main(void) {
    Tuple t1 = {5, 10};
    Tuple t2 = {3, 7};

    Tuple* result = pairwise_addition(&t1, &t2);

    if (result != NULL) {
        printf("Result: (%d, %d)\n", result->x, result->y);
        free(result);
        result = NULL;
    } else {
        printf("Error: Memory allocation or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}