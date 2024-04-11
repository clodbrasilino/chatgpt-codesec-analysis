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
    if(!trimmed){
        return NULL;
    }

    trimmed->size = tuple->size - k;
    trimmed->data = (int*)malloc(trimmed->size * sizeof(int));
    if(!trimmed->data){
        free(trimmed);
        return NULL;
    }

    for (int i = 0; i < trimmed->size; i++) {
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
    if(!tuple.data){
        return -1;
    }

    for (int i = 0; i < size; i++) {
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
    if(trimmed != NULL){
        free(trimmed->data);
        free(trimmed);
    }

    return 0;
}