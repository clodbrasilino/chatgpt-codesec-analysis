#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t size;
} TupleArray;

TupleArray remove_matching_tuples(const TupleArray* arr1, const TupleArray* arr2) {
    TupleArray result = {NULL, 0};
    
    if (!arr1 || !arr2 || !arr1->tuples || !arr2->tuples) {
        return result;
    }

    result.tuples = (Tuple*)malloc(arr1->size * sizeof(Tuple));
    if (!result.tuples) {
        return result;
    }

    for (size_t i = 0; i < arr1->size; ++i) {
        bool match = false;
        for (size_t j = 0; j < arr2->size; ++j) {
            if (arr1->tuples[i].x == arr2->tuples[j].x && arr1->tuples[i].y == arr2->tuples[j].y) {
                match = true;
                break;
            }
        }
        if (!match) {
            result.tuples[result.size++] = arr1->tuples[i];
        }
    }

    if (result.size == 0) {
        free(result.tuples);
        result.tuples = NULL;
    } else {
        Tuple* temp = (Tuple*)realloc(result.tuples, result.size * sizeof(Tuple));
        if (temp) {
            result.tuples = temp;
        }
    }

    return result;
}

int main(void) {
    Tuple t1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple t2[] = {{3, 4}, {7, 8}, {9, 10}};

    TupleArray arr1 = {t1, sizeof(t1) / sizeof(t1[0])};
    TupleArray arr2 = {t2, sizeof(t2) / sizeof(t2[0])};

    TupleArray result = remove_matching_tuples(&arr1, &arr2);

    for (size_t i = 0; i < result.size; ++i) {
        printf("(%d, %d)\n", result.tuples[i].x, result.tuples[i].y);
    }

    if (result.tuples) {
        free(result.tuples);
    }

    return 0;
}