#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    
    if (tupleA->size == 0 || tupleB->size == 0) {
        return 0;
    }
    
    int lastA = tupleA->elements[tupleA->size - 1];
    int lastB = tupleB->elements[tupleB->size - 1];
    
    if (lastA < lastB) return -1;
    if (lastA > lastB) return 1;
    return 0;
}

void sort_tuples_by_last_element(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main() {
    int elements1[] = {1, 2, 5};
    int elements2[] = {3, 1, 2};
    int elements3[] = {4, 7, 1};
    int elements4[] = {8, 9};

    Tuple tuples[] = {
        {elements1, sizeof(elements1) / sizeof(elements1[0])},
        {elements2, sizeof(elements2) / sizeof(elements2[0])},
        {elements3, sizeof(elements3) / sizeof(elements3[0])},
        {elements4, sizeof(elements4) / sizeof(elements4[0])}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples_by_last_element(tuples, count);

    for (size_t i = 0; i < count; i++) {
        printf("(");
        for (size_t j = 0; j < tuples[i].size; j++) {
            printf("%d%s", tuples[i].elements[j], j < tuples[i].size - 1 ? ", " : "");
        }
        printf(")\n");
    }

    return 0;
}