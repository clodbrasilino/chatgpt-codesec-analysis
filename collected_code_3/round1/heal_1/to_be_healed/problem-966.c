#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int size;
} TupleList;

void removeEmptyTuples(TupleList *list) {
    int i, j;
    for (i = 0; i < list->size; i++) {
        if (list->tuples[i].size == 0) {
            for (j = i; j < list->size - 1; j++) {
                /* Possible weaknesses found:
                 *  use of uninitialized value '*_6 + _9' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
                 */
                list->tuples[j] = list->tuples[j + 1];
            }
            list->size--;
            i--;
        }
    }
}

int main() {
    TupleList list;
    list.size = 5;
    list.tuples = (Tuple*)malloc(list.size * sizeof(Tuple));

    for (int i = 0; i < list.size; i++) {
        if (i % 2 == 0) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'list.tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            list.tuples[i].size = 0;
            list.tuples[i].data = NULL;
        } else {
            list.tuples[i].size = 1;
            list.tuples[i].data = (int*)malloc(sizeof(int));
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*_24 + _26.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            list.tuples[i].data[0] = i;
        }
    }

    removeEmptyTuples(&list);

    for (int i = 0; i < list.size; i++) {
        printf("Tuple %d size: %d\n", i, list.tuples[i].size);
    }

    for (int i = 0; i < list.size; i++) {
        free(list.tuples[i].data);
    }
    free(list.tuples);

    return 0;
}