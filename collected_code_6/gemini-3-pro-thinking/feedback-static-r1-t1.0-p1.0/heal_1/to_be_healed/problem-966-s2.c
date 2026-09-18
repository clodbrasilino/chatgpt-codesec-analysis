#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

int addTuple(TupleList *list, const int *data, size_t size);
void removeEmptyTuples(TupleList *list);
void freeList(TupleList *list);
void printList(const TupleList *list);

int addTuple(TupleList *list, const int *data, size_t size) {
    if (!list) {
        return 0;
    }

    if (list->count >= list->capacity) {
        size_t new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        Tuple *new_tuples = realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (!new_tuples) {
            return 0;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }

    int *new_data = NULL;
    if (size > 0 && data != NULL) {
        new_data = malloc(size * sizeof(int));
        if (!new_data) {
            return 0;
        }
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
    } else if (size > 0 && data == NULL) {
        return 0;
    }

    list->tuples[list->count].data = new_data;
    list->tuples[list->count].size = size;
    list->count++;

    return 1;
}

void removeEmptyTuples(TupleList *list) {
    if (!list || !list->tuples) {
        return;
    }

    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->count; ++read_index) {
        if (list->tuples[read_index].size == 0) {
            free(list->tuples[read_index].data);
            list->tuples[read_index].data = NULL;
        } else {
            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
            }
            write_index++;
        }
    }
    list->count = write_index;
}

void freeList(TupleList *list) {
    if (!list) {
        return;
    }
    if (list->tuples) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
        }
        free(list->tuples);
        list->tuples = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

void printList(const TupleList *list) {
    if (!list || !list->tuples) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            printf("%d%s", list->tuples[i].data[j], j < list->tuples[i].size - 1 ? ", " : "");
        }
        printf(")\n");
    }
}

int main(void) {
    TupleList list = {NULL, 0, 0};
    int status = EXIT_SUCCESS;

    /* Possible weaknesses found:
     *  Variable 'data1' can be declared as const array [constVariable]
     */
    int data1[] = {1, 2};
    /* Possible weaknesses found:
     *  Variable 'data2' can be declared as const array [constVariable]
     */
    int data2[] = {3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'data3' can be declared as const array [constVariable]
     */
    int data3[] = {6};

    if (!addTuple(&list, data1, 2)) goto cleanup_error;
    if (!addTuple(&list, NULL, 0)) goto cleanup_error;
    if (!addTuple(&list, data2, 3)) goto cleanup_error;
    if (!addTuple(&list, NULL, 0)) goto cleanup_error;
    if (!addTuple(&list, data3, 1)) goto cleanup_error;
    if (!addTuple(&list, NULL, 0)) goto cleanup_error;

    removeEmptyTuples(&list);
    printList(&list);

    goto cleanup_success;

cleanup_error:
    status = EXIT_FAILURE;

cleanup_success:
    freeList(&list);
    return status;
}