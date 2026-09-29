#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

int create_tuple(Tuple *t, const int *values, size_t length)
{
    if (t == NULL || (values == NULL && length > 0)) {
        return -1;
    }

    t->elements = NULL;
    t->length = length;

    if (length > 0) {
        t->elements = malloc(length * sizeof(int));
        if (t->elements == NULL) {
            return -1;
        }
        for (size_t i = 0; i < length; i++) {
            t->elements[i] = values[i];
        }
    }

    return 0;
}

void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->length = 0;
    }
}

void free_tuple_list(TupleList *list)
{
    if (list != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free_tuple(&list->tuples[i]);
        }
        free(list->tuples);
        list->tuples = NULL;
        list->count = 0;
    }
}

int remove_tuples_of_length(TupleList *list, size_t k)
{
    if (list == NULL) {
        return -1;
    }

    size_t write_index = 0;

    for (size_t i = 0; i < list->count; i++) {
        if (list->tuples[i].length == k) {
            free_tuple(&list->tuples[i]);
        } else {
            if (write_index != i) {
                list->tuples[write_index] = list->tuples[i];
            }
            write_index++;
        }
    }

    list->count = write_index;

    if (write_index == 0) {
        free(list->tuples);
        list->tuples = NULL;
    } else {
        Tuple *resized = realloc(list->tuples, write_index * sizeof(Tuple));
        if (resized != NULL) {
            list->tuples = resized;
        }
    }

    return 0;
}

void print_tuple_list(const TupleList *list)
{
    if (list == NULL) {
        return;
    }

    printf("[");
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].length; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j + 1 < list->tuples[i].length) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1 < list->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int data1[] = {4, 5};
    int data2[] = {4};
    int data3[] = {8, 6, 7};
    int data4[] = {1};
    int data5[] = {3, 4, 6, 7};

    TupleList list;
    list.count = 5;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (create_tuple(&list.tuples[0], data1, 2) != 0 ||
        create_tuple(&list.tuples[1], data2, 1) != 0 ||
        create_tuple(&list.tuples[2], data3, 3) != 0 ||
        create_tuple(&list.tuples[3], data4, 1) != 0 ||
        create_tuple(&list.tuples[4], data5, 4) != 0) {
        fprintf(stderr, "Tuple creation failed\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    print_tuple_list(&list);

    size_t k = 1;
    if (remove_tuples_of_length(&list, k) != 0) {
        fprintf(stderr, "Removal failed\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("After removing tuples of length %zu: ", k);
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}