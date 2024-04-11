#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *data;
    int size;
} Tuple;

Tuple* trimTuple(Tuple* tuple, int k) {
    if (k >= tuple->size) {
        return NULL;
    }

    Tuple* trimmed = (Tuple*)malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'trimmed' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    trimmed->size = tuple->size - k;
    trimmed->data = (int*)malloc(trimmed->size * sizeof(int));

    for (int i = 0; i < trimmed->size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*trimmed.data + (long unsigned int)i * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        trimmed->data[i] = tuple->data[i];
    }

    return trimmed;
}

int main() {
    int size = 5;
    int k = 2;
    Tuple tuple;
    tuple.size = size;
    tuple.data = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuple.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple.data[i] = i + 1;
    }

    Tuple* trimmed = trimTuple(&tuple, k);

    if (trimmed != NULL) {
        for (int i = 0; i < trimmed->size; i++) {
            printf("%d ", trimmed->data[i]);
        }
        printf("\n");
    } else {
        printf("Cannot trim the tuple by %d\n", k);
    }

    free(tuple.data);
    free(trimmed->data);
    free(trimmed);

    return 0;
}