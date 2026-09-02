#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int tuple_compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    if (tupleA->a != tupleB->a) return tupleA->a - tupleB->a;
    return tupleA->b - tupleB->b;
}

void count_unique_tuples(TupleList *list) {
    qsort(list->tuples, list->count, sizeof(Tuple), tuple_compare);
    int unique_count = 1;
    for (int i = 1; i < list->count; i++) {
        if (list->tuples[i].a != list->tuples[i-1].a || list->tuples[i].b != list->tuples[i-1].b) {
            unique_count++;
        }
    }
    printf("Unique tuples: %d\n", unique_count);
}

int main() {
    TupleList list;
    list.count = 5;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    list.tuples[0] = (Tuple){1, 2};
    list.tuples[1] = (Tuple){3, 4};
    list.tuples[2] = (Tuple){1, 2};
    list.tuples[3] = (Tuple){5, 6};
    list.tuples[4] = (Tuple){3, 4};

    count_unique_tuples(&list);

    free(list.tuples);
    return 0;
}