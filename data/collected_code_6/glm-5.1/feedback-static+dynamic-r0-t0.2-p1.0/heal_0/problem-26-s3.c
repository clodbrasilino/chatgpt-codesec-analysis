#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

bool has_all_k_elements(TupleList list, int k) {
    if (list.tuples == NULL) {
        return false;
    }

    for (int i = 0; i < list.count; i++) {
        if (list.tuples[i].elements == NULL) {
            return false;
        }
        if (list.tuples[i].size != k) {
            return false;
        }
    }

    return true;
}

int main() {
    Tuple t1 = { .elements = malloc(3 * sizeof(int)), .size = 3 };
    Tuple t2 = { .elements = malloc(3 * sizeof(int)), .size = 3 };
    Tuple t3 = { .elements = malloc(2 * sizeof(int)), .size = 2 };

    if (t1.elements == NULL || t2.elements == NULL || t3.elements == NULL) {
        free(t1.elements);
        free(t2.elements);
        free(t3.elements);
        return EXIT_FAILURE;
    }

    TupleList list1 = { .tuples = malloc(2 * sizeof(Tuple)), .count = 2 };
    if (list1.tuples == NULL) {
        free(t1.elements);
        free(t2.elements);
        free(t3.elements);
        return EXIT_FAILURE;
    }
    list1.tuples[0] = t1;
    list1.tuples[1] = t2;

    bool result1 = has_all_k_elements(list1, 3);
    printf("%d\n", result1);

    TupleList list2 = { .tuples = malloc(2 * sizeof(Tuple)), .count = 2 };
    if (list2.tuples == NULL) {
        free(list1.tuples);
        free(t1.elements);
        free(t2.elements);
        free(t3.elements);
        return EXIT_FAILURE;
    }
    list2.tuples[0] = t1;
    list2.tuples[1] = t3;

    bool result2 = has_all_k_elements(list2, 3);
    printf("%d\n", result2);

    free(list1.tuples);
    free(list2.tuples);
    free(t1.elements);
    free(t2.elements);
    free(t3.elements);

    return EXIT_SUCCESS;
}