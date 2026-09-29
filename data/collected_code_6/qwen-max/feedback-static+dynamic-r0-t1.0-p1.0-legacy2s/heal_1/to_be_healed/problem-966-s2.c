#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t count;
} TupleList;

Tuple* createTuple(size_t size) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    t->elements = (int*)calloc(size, sizeof(int));
    t->size = size;
    return t;
}

void freeTuple(Tuple *t) {
    free(t->elements);
    free(t);
}

TupleList* createTupleList() {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    list->tuples = NULL;
    list->count = 0;
    return list;
}

/* Possible weaknesses found:
 *  Parameter 't' can be declared as pointer to const [constParameterPointer]
 */
void addTuple(TupleList *list, Tuple *t) {
    list->tuples = (Tuple*)realloc(list->tuples, (list->count + 1) * sizeof(Tuple));
    list->tuples[list->count] = *t;
    list->count++;
}

void removeEmptyTuples(TupleList *list) {
    if (list->count == 0) return;

    Tuple *newTuples = (Tuple*)malloc(list->count * sizeof(Tuple));
    size_t newCount = 0;

    for (size_t i = 0; i < list->count; i++) {
        if (list->tuples[i].size > 0) {
            newTuples[newCount++] = list->tuples[i];
        }
    }

    free(list->tuples);
    list->tuples = newTuples;
    list->count = newCount;
}

int main() {
    TupleList *list = createTupleList();

    Tuple *t1 = createTuple(3);
    t1->elements[0] = 1;
    t1->elements[1] = 2;
    t1->elements[2] = 3;
    addTuple(list, t1);

    Tuple *t2 = createTuple(0);
    addTuple(list, t2);

    Tuple *t3 = createTuple(2);
    t3->elements[0] = 4;
    t3->elements[1] = 5;
    addTuple(list, t3);

    removeEmptyTuples(list);

    for (size_t i = 0; i < list->count; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            printf("%d ", list->tuples[i].elements[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < list->count; i++) {
        freeTuple(&list->tuples[i]);
    }
    free(list->tuples);
    free(list);

    return 0;
}