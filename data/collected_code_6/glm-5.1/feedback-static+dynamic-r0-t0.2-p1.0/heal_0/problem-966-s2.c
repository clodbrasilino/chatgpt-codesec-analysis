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

    Tuple *temp = (Tuple *)realloc(result.tuples, result.count * sizeof(Tuple));
    if (temp != NULL || result.count == 0) {
        result.tuples = temp;
    }

    return result;
}

int main() {
    Tuple tuples[4];
    
    tuples[0].elements = (int *)malloc(2 * sizeof(int));
    tuples[0].elements[0] = 1;
    tuples[0].elements[1] = 2;
    tuples[0].size = 2;

    tuples[1].elements = NULL;
    tuples[1].size = 0;

    tuples[2].elements = (int *)malloc(1 * sizeof(int));
    tuples[2].elements[0] = 3;
    tuples[2].size = 1;

    tuples[3].elements = NULL;
    tuples[3].size = 0;

    TupleList list;
    list.tuples = tuples;
    list.count = 4;

    TupleList new_list = remove_empty_tuples(list);

    for (int i = 0; i < new_list.count; i++) {
        printf("Tuple %d (size %d): ", i, new_list.tuples[i].size);
        for (int j = 0; j < new_list.tuples[i].size; j++) {
            printf("%d ", new_list.tuples[i].elements[j]);
        }
        printf("\n");
    }

    free(tuples[0].elements);
    free(tuples[2].elements);
    free(new_list.tuples);

    return 0;
}