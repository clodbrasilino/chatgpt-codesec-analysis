#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *data;
    size_t size;
};

struct TupleList {
    struct Tuple *tuples;
    size_t count;
};

void remove_empty_tuples(struct TupleList *list) {
    if (!list || !list->tuples) {
        return;
    }

    size_t write_index = 0;

    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size == 0) {
            if (list->tuples[i].data) {
                free(list->tuples[i].data);
                list->tuples[i].data = NULL;
            }
        } else {
            if (write_index != i) {
                list->tuples[write_index] = list->tuples[i];
            }
            write_index++;
        }
    }

    list->count = write_index;
}

void free_tuple_list(struct TupleList *list) {
    if (!list || !list->tuples) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].data) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
        }
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void) {
    struct TupleList list = {0};
    
    list.count = 3;
    list.tuples = (struct Tuple *)calloc(list.count, sizeof(struct Tuple));
    if (!list.tuples) {
        return EXIT_FAILURE;
    }

    list.tuples[0].size = 2;
    list.tuples[0].data = (int *)malloc(2 * sizeof(int));
    if (list.tuples[0].data) {
        list.tuples[0].data[0] = 10;
        list.tuples[0].data[1] = 20;
    } else {
        list.tuples[0].size = 0;
    }

    list.tuples[1].size = 0;
    list.tuples[1].data = NULL;

    list.tuples[2].size = 1;
    list.tuples[2].data = (int *)malloc(1 * sizeof(int));
    if (list.tuples[2].data) {
        list.tuples[2].data[0] = 30;
    } else {
        list.tuples[2].size = 0;
    }

    remove_empty_tuples(&list);

    free_tuple_list(&list);

    return EXIT_SUCCESS;
}