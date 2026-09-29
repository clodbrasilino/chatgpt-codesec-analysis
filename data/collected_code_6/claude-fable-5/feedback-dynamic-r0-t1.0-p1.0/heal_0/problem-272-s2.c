#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

int extract_rear_elements(const TupleList *list, int **result, size_t *result_count)
{
    size_t i;
    int *output;

    if (list == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    if (list->count == 0 || list->tuples == NULL) {
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    output = malloc(list->count * sizeof(int));
    if (output == NULL) {
        return -1;
    }

    for (i = 0; i < list->count; i++) {
        if (list->tuples[i].elements == NULL || list->tuples[i].count == 0) {
            free(output);
            return -1;
        }
        output[i] = list->tuples[i].elements[list->tuples[i].count - 1];
    }

    *result = output;
    *result_count = list->count;
    return 0;
}

int create_tuple(Tuple *tuple, const int *values, size_t count)
{
    size_t i;

    if (tuple == NULL || values == NULL || count == 0) {
        return -1;
    }

    tuple->elements = malloc(count * sizeof(int));
    if (tuple->elements == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        tuple->elements[i] = values[i];
    }
    tuple->count = count;
    return 0;
}

void free_tuple_list(TupleList *list)
{
    size_t i;

    if (list == NULL || list->tuples == NULL) {
        return;
    }

    for (i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
        list->tuples[i].elements = NULL;
        list->tuples[i].count = 0;
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void)
{
    TupleList list;
    int *rear_elements = NULL;
    size_t rear_count = 0;
    size_t i;
    int status;

    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6, 7, 8, 9};

    list.count = 3;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < list.count; i++) {
        list.tuples[i].elements = NULL;
        list.tuples[i].count = 0;
    }

    if (create_tuple(&list.tuples[0], data1, sizeof(data1) / sizeof(data1[0])) != 0 ||
        create_tuple(&list.tuples[1], data2, sizeof(data2) / sizeof(data2[0])) != 0 ||
        create_tuple(&list.tuples[2], data3, sizeof(data3) / sizeof(data3[0])) != 0) {
        fprintf(stderr, "Tuple creation failed\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    status = extract_rear_elements(&list, &rear_elements, &rear_count);
    if (status != 0) {
        fprintf(stderr, "Extraction failed\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Rear elements: ");
    for (i = 0; i < rear_count; i++) {
        printf("%d ", rear_elements[i]);
    }
    printf("\n");

    free(rear_elements);
    free_tuple_list(&list);
    return EXIT_SUCCESS;
}