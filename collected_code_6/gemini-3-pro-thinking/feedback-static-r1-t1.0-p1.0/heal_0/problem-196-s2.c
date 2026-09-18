#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

void remove_tuples_with_length_k(TupleList *list, size_t k) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    size_t new_count = 0;
    for (size_t i = 0; i < list->count; i++) {
        if (list->tuples[i].length == k) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
            list->tuples[i].length = 0;
        } else {
            if (new_count != i) {
                list->tuples[new_count] = list->tuples[i];
            }
            new_count++;
        }
    }
    list->count = new_count;
}

int main(void) {
    TupleList list;
    list.count = 3;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }

    list.tuples[0].length = 2;
    list.tuples[0].data = (int *)malloc(2 * sizeof(int));
    
    list.tuples[1].length = 3;
    list.tuples[1].data = (int *)malloc(3 * sizeof(int));
    
    list.tuples[2].length = 2;
    list.tuples[2].data = (int *)malloc(2 * sizeof(int));

    if (list.tuples[0].data == NULL || list.tuples[1].data == NULL || list.tuples[2].data == NULL) {
        for (size_t i = 0; i < list.count; i++) {
            free(list.tuples[i].data);
        }
        free(list.tuples);
        return EXIT_FAILURE;
    }

    list.tuples[0].data[0] = 1;
    list.tuples[0].data[1] = 2;

    list.tuples[1].data[0] = 3;
    list.tuples[1].data[1] = 4;
    list.tuples[1].data[2] = 5;

    list.tuples[2].data[0] = 6;
    list.tuples[2].data[1] = 7;

    remove_tuples_with_length_k(&list, 2);

    for (size_t i = 0; i < list.count; i++) {
        for (size_t j = 0; j < list.tuples[i].length; j++) {
            printf("%d ", list.tuples[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].data);
    }
    free(list.tuples);

    return EXIT_SUCCESS;
}