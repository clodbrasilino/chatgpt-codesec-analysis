#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *values;
    int size;
} Tuple;

typedef struct TupleList {
    Tuple *tuples;
    int size;
} TupleList;

int isNoneTuple(Tuple tuple) {
    for (int i = 0; i < tuple.size; i++) {
        if (tuple.values[i] != 0) {
            return 0;
        }
    }
    return 1;
}

TupleList removeNoneTuples(TupleList list) {
    int noneCount = 0;
    for (int i = 0; i < list.size; i++) {
        if (isNoneTuple(list.tuples[i])) {
            noneCount++;
        }
    }

    if (list.size == noneCount) {
        return (TupleList) { .tuples = NULL, .size = 0 };
    }

    Tuple *newTuples = malloc((list.size - noneCount) * sizeof(Tuple));
    if (!newTuples) {
        return (TupleList) { .tuples = NULL, .size = 0 };
    }

    int newIndex = 0;
    for (int i = 0; i < list.size; i++) {
        if (!isNoneTuple(list.tuples[i])) {
            newTuples[newIndex++] = list.tuples[i];
        }
    }

    return (TupleList) { .tuples = newTuples, .size = list.size - noneCount };
}

int main() {
    Tuple tuple1 = { .values = (int[]){0, 0, 0}, .size = 3 };
    Tuple tuple2 = { .values = (int[]){1, 2, 3}, .size = 3 };
    Tuple tuple3 = { .values = (int[]){0, 0, 0}, .size = 3 };
    Tuple tuple4 = { .values = (int[]){4, 5, 6}, .size = 3 };

    TupleList list = { .tuples = (Tuple[]){tuple1, tuple2, tuple3, tuple4}, .size = 4 };
    TupleList newList = removeNoneTuples(list);

    if (newList.tuples) {
        for (int i = 0; i < newList.size; i++) {
            for (int j = 0; j < newList.tuples[i].size; j++) {
                printf("%d ", newList.tuples[i].values[j]);
            }
            printf("\n");
        }
    }

    free(newList.tuples);
    return 0;
}