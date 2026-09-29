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

    Tuple *newTuples = malloc((list.size - noneCount) * sizeof(Tuple));
    int newIndex = 0;
    for (int i = 0; i < list.size; i++) {
        if (!isNoneTuple(list.tuples[i])) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newTuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newTuples[newIndex++] = list.tuples[i];
        }
    }

    TupleList newList;
    newList.tuples = newTuples;
    newList.size = list.size - noneCount;
    return newList;
}

int main() {
    Tuple tuple1 = { .values = (int[]){0, 0, 0}, .size = 3 };
    Tuple tuple2 = { .values = (int[]){1, 2, 3}, .size = 3 };
    Tuple tuple3 = { .values = (int[]){0, 0, 0}, .size = 3 };
    Tuple tuple4 = { .values = (int[]){4, 5, 6}, .size = 3 };

    TupleList list = { .tuples = (Tuple[]){tuple1, tuple2, tuple3, tuple4}, .size = 4 };
    TupleList newList = removeNoneTuples(list);

    for (int i = 0; i < newList.size; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*_10 + _12.size' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'newList.tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        for (int j = 0; j < newList.tuples[i].size; j++) {
            printf("%d ", newList.tuples[i].values[j]);
        }
        printf("\n");
    }

    free(newList.tuples);
    return 0;
}