#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

TupleList remove_empty_tuples(TupleList list) {
    TupleList result;
    result.count = 0;
    result.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (result.tuples == NULL) {
        result.tuples = NULL;
        result.count = 0;
        return result;
    }

    for (int i = 0; i < list.count; i++) {
        if (list.tuples[i].size > 0) {
            result.tuples[result.count] = list.tuples[i];
            result.count++;
        }
    }

    Tuple *shrunk = (Tuple *)realloc(result.tuples, result.count * sizeof(Tuple));
    if (shrunk != NULL || result.count == 0) {
        result.tuples = shrunk;
    }

    return result;
}

int main() {
    Tuple t1 = {(int[]){1, 2}, 2};
    Tuple t2 = {NULL, 0};
    Tuple t3 = {(int[]){3}, 1};
    Tuple t4 = {NULL, 0};

    TupleList list;
    list.count = 4;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        return 1;
    }
    list.tuples[0] = t1;
    list.tuples[1] = t2;
    list.tuples[2] = t3;
    list.tuples[3] = t4;

    TupleList new_list = remove_empty_tuples(list);

    for (int i = 0; i < new_list.count; i++) {
        printf("Tuple %d (size %d): ", i, new_list.tuples[i].size);
        for (int j = 0; j < new_list.tuples[i].size; j++) {
            printf("%d ", new_list.tuples[i].elements[j]);
        }
        printf("\n");
    }

    free(list.tuples);
    free(new_list.tuples);

    return 0;
}