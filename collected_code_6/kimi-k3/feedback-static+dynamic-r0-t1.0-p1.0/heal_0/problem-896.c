#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

static int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int last_a = ta->elements[ta->size - 1];
    int last_b = tb->elements[tb->size - 1];
    return (last_a > last_b) - (last_a < last_b);
}

static void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
    }
    list->tuples = NULL;
    list->size = 0;
}

int sort_tuples_by_last_element(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return -1;
    }
    if (list->size == 0) {
        return 0;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (list->tuples[i].elements == NULL || list->tuples[i].size == 0) {
            return -1;
        }
    }
    qsort(list->tuples, list->size, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void) {
    TupleList list = {0};
    int status = 0;
    int data[5][3] = {
        {1, 2, 5},
        {3, 1, 2},
        {4, 4, 1},
        {0, 0, 9},
        {2, 3, 3}
    };
    size_t tuple_sizes[5] = {3, 3, 3, 3, 3};

    list.size = 5;
    list.tuples = (Tuple *)calloc(list.size, sizeof(Tuple));
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.size; i++) {
        list.tuples[i].size = tuple_sizes[i];
        list.tuples[i].elements = (int *)malloc(tuple_sizes[i] * sizeof(int));
        if (list.tuples[i].elements == NULL) {
            free_tuple_list(&list);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < tuple_sizes[i]; j++) {
            list.tuples[i].elements[j] = data[i][j];
        }
    }

    if (sort_tuples_by_last_element(&list) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.size; i++) {
        printf("(");
        for (size_t j = 0; j < list.tuples[i].size; j++) {
            printf("%d", list.tuples[i].elements[j]);
            if (j < list.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(&list);
    return status;
}