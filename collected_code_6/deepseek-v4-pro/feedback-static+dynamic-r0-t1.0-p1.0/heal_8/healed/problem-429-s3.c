#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple tuple1;
    Tuple tuple2;
} TuplePair;

Tuple create_tuple(const int *data, size_t size) {
    Tuple tuple;
    tuple.size = size;
    if (size > 0) {
        if (size > SIZE_MAX / sizeof(int)) {
            exit(EXIT_FAILURE);
        }
        tuple.elements = (int *)malloc(size * sizeof(int));
        if (tuple.elements == NULL) {
            exit(EXIT_FAILURE);
        }
        if (data != NULL) {
            memcpy(tuple.elements, data, size * sizeof(int));
        } else {
            memset(tuple.elements, 0, size * sizeof(int));
        }
    } else {
        tuple.elements = NULL;
    }
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

Tuple elementwise_tuple(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL || t1->size != t2->size) {
        exit(EXIT_FAILURE);
    }
    Tuple result = create_tuple(NULL, t1->size);
    for (size_t i = 0; i < result.size; i++) {
        result.elements[i] = t1->elements[i] * t2->elements[i];
    }
    return result;
}

TuplePair tuples_from_pair(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL || t1->size != t2->size) {
        exit(EXIT_FAILURE);
    }
    TuplePair pair;
    pair.tuple1.size = t1->size;
    pair.tuple1.elements = NULL;
    pair.tuple2.size = t2->size;
    pair.tuple2.elements = NULL;

    if (t1->size > SIZE_MAX / sizeof(int)) {
        exit(EXIT_FAILURE);
    }
    pair.tuple1.elements = (int *)malloc(t1->size * sizeof(int));
    if (pair.tuple1.elements == NULL) {
        exit(EXIT_FAILURE);
    }
    
    if (t2->size > SIZE_MAX / sizeof(int)) {
        free(pair.tuple1.elements);
        pair.tuple1.elements = NULL;
        pair.tuple1.size = 0;
        exit(EXIT_FAILURE);
    }
    pair.tuple2.elements = (int *)malloc(t2->size * sizeof(int));
    if (pair.tuple2.elements == NULL) {
        free(pair.tuple1.elements);
        pair.tuple1.elements = NULL;
        pair.tuple1.size = 0;
        exit(EXIT_FAILURE);
    }
    
    memcpy(pair.tuple1.elements, t1->elements, t1->size * sizeof(int));
    memcpy(pair.tuple2.elements, t2->elements, t2->size * sizeof(int));
    for (size_t i = 0; i < t1->size; i++) {
        pair.tuple1.elements[i] = t1->elements[i] + t2->elements[i];
        pair.tuple2.elements[i] = t1->elements[i] - t2->elements[i];
    }
    return pair;
}

void free_tuple_pair(TuplePair *pair) {
    if (pair != NULL) {
        free_tuple(&pair->tuple1);
        free_tuple(&pair->tuple2);
    }
}

int main(void) {
    const int data1[] = {1, 2, 3, 4};
    const int data2[] = {5, 6, 7, 8};
    size_t size = sizeof(data1) / sizeof(data1[0]);

    Tuple t1 = create_tuple(data1, size);
    Tuple t2 = create_tuple(data2, size);

    Tuple elementwise = elementwise_tuple(&t1, &t2);
    printf("Elementwise tuple: ");
    for (size_t i = 0; i < elementwise.size; i++) {
        printf("%d ", elementwise.elements[i]);
    }
    printf("\n");

    TuplePair pair = tuples_from_pair(&t1, &t2);
    printf("Tuple pair - tuple1: ");
    for (size_t i = 0; i < pair.tuple1.size; i++) {
        printf("%d ", pair.tuple1.elements[i]);
    }
    printf("\n");
    printf("Tuple pair - tuple2: ");
    for (size_t i = 0; i < pair.tuple2.size; i++) {
        printf("%d ", pair.tuple2.elements[i]);
    }
    printf("\n");

    free_tuple(&elementwise);
    free_tuple_pair(&pair);
    free_tuple(&t1);
    free_tuple(&t2);

    return 0;
}