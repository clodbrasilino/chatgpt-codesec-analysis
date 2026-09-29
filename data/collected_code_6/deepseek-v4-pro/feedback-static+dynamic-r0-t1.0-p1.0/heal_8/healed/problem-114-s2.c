#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Tuple {
    int *data;
    size_t size;
    int frequency;
} Tuple;

typedef struct TupleList {
    Tuple *tuples;
    size_t count;
} TupleList;

int tuple_equals(const Tuple *a, const Tuple *b) {
    if (a == NULL || b == NULL) return 0;
    if (a->size != b->size) return 0;
    if (a->data == NULL && b->data == NULL) return 1;
    if (a->data == NULL || b->data == NULL) return 0;
    for (size_t i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) return 0;
    }
    return 1;
}

Tuple tuple_copy(const Tuple *src) {
    Tuple dst;
    dst.size = 0;
    dst.data = NULL;
    dst.frequency = 0;

    if (src == NULL) return dst;

    dst.size = src->size;
    if (src->size > 0 && src->data != NULL) {
        if (src->size > SIZE_MAX / sizeof(int)) {
            exit(EXIT_FAILURE);
        }
        size_t alloc_size = src->size * sizeof(int);
        dst.data = (int *)malloc(alloc_size);
        if (dst.data == NULL) {
            exit(EXIT_FAILURE);
        }
        memmove(dst.data, src->data, alloc_size);
    } else {
        dst.data = NULL;
    }
    dst.frequency = 0;
    return dst;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
        t->frequency = 0;
    }
}

void assign_frequencies(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count == 0) {
        return;
    }

    for (size_t i = 0; i < list->count; i++) {
        list->tuples[i].frequency = 0;
    }

    for (size_t i = 0; i < list->count; i++) {
        if (list->tuples[i].frequency == 0) {
            int count = 0;
            for (size_t j = 0; j < list->count; j++) {
                if (tuple_equals(&list->tuples[i], &list->tuples[j])) {
                    count++;
                }
            }
            for (size_t j = 0; j < list->count; j++) {
                if (tuple_equals(&list->tuples[i], &list->tuples[j])) {
                    list->tuples[j].frequency = count;
                }
            }
        }
    }
}

static int initialize_tuple_from_array(Tuple *tuple, const int *data, size_t size) {
    if (tuple == NULL || (size > 0 && data == NULL)) {
        return 0;
    }

    tuple->size = size;
    tuple->frequency = 0;

    if (size == 0) {
        tuple->data = NULL;
        return 1;
    }

    if (size > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    tuple->data = (int *)malloc(size * sizeof(int));
    if (tuple->data == NULL) {
        return 0;
    }

    memmove(tuple->data, data, size * sizeof(int));
    return 1;
}

static void free_tuples_partial(Tuple *tuples, size_t count) {
    if (tuples == NULL) return;
    for (size_t i = 0; i < count; i++) {
        free(tuples[i].data);
        tuples[i].data = NULL;
    }
    free(tuples);
}

int main(void) {
    TupleList list;
    list.count = 5;
    list.tuples = (Tuple *)calloc(list.count, sizeof(Tuple));
    if (list.tuples == NULL) {
        return EXIT_FAILURE;
    }

    int data0[] = {1, 2, 3};
    int data1[] = {4, 5};
    int data2[] = {1, 2, 3};
    int data3[] = {6};
    int data4[] = {4, 5};

    size_t size0 = sizeof(data0) / sizeof(data0[0]);
    size_t size1 = sizeof(data1) / sizeof(data1[0]);
    size_t size2 = sizeof(data2) / sizeof(data2[0]);
    size_t size3 = sizeof(data3) / sizeof(data3[0]);
    size_t size4 = sizeof(data4) / sizeof(data4[0]);

    if (!initialize_tuple_from_array(&list.tuples[0], data0, size0)) {
        free_tuples_partial(list.tuples, 0);
        return EXIT_FAILURE;
    }
    if (!initialize_tuple_from_array(&list.tuples[1], data1, size1)) {
        free_tuples_partial(list.tuples, 1);
        return EXIT_FAILURE;
    }
    if (!initialize_tuple_from_array(&list.tuples[2], data2, size2)) {
        free_tuples_partial(list.tuples, 2);
        return EXIT_FAILURE;
    }
    if (!initialize_tuple_from_array(&list.tuples[3], data3, size3)) {
        free_tuples_partial(list.tuples, 3);
        return EXIT_FAILURE;
    }
    if (!initialize_tuple_from_array(&list.tuples[4], data4, size4)) {
        free_tuples_partial(list.tuples, 4);
        return EXIT_FAILURE;
    }

    assign_frequencies(&list);

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu: (", i);
        for (size_t j = 0; j < list.tuples[i].size; j++) {
            printf("%d", list.tuples[i].data[j]);
            if (j + 1 < list.tuples[i].size) printf(", ");
        }
        printf(") frequency = %d\n", list.tuples[i].frequency);
    }

    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].data);
    }
    free(list.tuples);

    return EXIT_SUCCESS;
}