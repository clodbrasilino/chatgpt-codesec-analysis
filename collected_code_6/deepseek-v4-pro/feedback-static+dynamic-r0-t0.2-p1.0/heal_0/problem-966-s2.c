#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *data;
    size_t size;
} Tuple;

typedef struct TupleList {
    Tuple *tuples;
    size_t count;
} TupleList;

int remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return -1;
    }

    size_t write_index = 0;

    for (size_t i = 0; i < list->count; i++) {
        if (list->tuples[i].size == 0) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
        } else {
            if (write_index != i) {
                list->tuples[write_index] = list->tuples[i];
                list->tuples[i].data = NULL;
                list->tuples[i].size = 0;
            }
            write_index++;
        }
    }

    list->count = write_index;

    Tuple *new_tuples = realloc(list->tuples, list->count * sizeof(Tuple));
    if (new_tuples == NULL && list->count > 0) {
        return -1;
    }
    list->tuples = new_tuples;

    return 0;
}

int main(void) {
    TupleList list;
    list.count = 4;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        return 1;
    }

    list.tuples[0].size = 0;
    list.tuples[0].data = NULL;

    list.tuples[1].size = 3;
    list.tuples[1].data = malloc(3 * sizeof(int));
    if (list.tuples[1].data == NULL) {
        free(list.tuples);
        return 1;
    }
    list.tuples[1].data[0] = 1;
    list.tuples[1].data[1] = 2;
    list.tuples[1].data[2] = 3;

    list.tuples[2].size = 0;
    list.tuples[2].data = NULL;

    list.tuples[3].size = 2;
    list.tuples[3].data = malloc(2 * sizeof(int));
    if (list.tuples[3].data == NULL) {
        free(list.tuples[1].data);
        free(list.tuples);
        return 1;
    }
    list.tuples[3].data[0] = 4;
    list.tuples[3].data[1] = 5;

    if (remove_empty_tuples(&list) != 0) {
        for (size_t i = 0; i < list.count; i++) {
            free(list.tuples[i].data);
        }
        free(list.tuples);
        return 1;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list.tuples[i].size; j++) {
            printf("%d ", list.tuples[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].data);
    }
    free(list.tuples);

    return 0;
}