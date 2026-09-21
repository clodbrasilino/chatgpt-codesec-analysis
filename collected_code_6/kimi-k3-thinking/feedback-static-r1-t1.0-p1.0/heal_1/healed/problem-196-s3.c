#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

int tuple_list_init(TupleList *list, size_t capacity);
void tuple_list_free(TupleList *list);
int tuple_list_add(TupleList *list, const int *data, size_t length);
size_t remove_tuples_of_length(TupleList *list, size_t k);

int tuple_list_init(TupleList *list, size_t capacity)
{
    if (list == NULL || capacity == 0) {
        return -1;
    }
    list->tuples = calloc(capacity, sizeof(Tuple));
    if (list->tuples == NULL) {
        list->count = 0;
        list->capacity = 0;
        return -1;
    }
    list->count = 0;
    list->capacity = capacity;
    return 0;
}

void tuple_list_free(TupleList *list)
{
    if (list == NULL) {
        return;
    }
    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
            list->tuples[i].length = 0;
        }
        free(list->tuples);
        list->tuples = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

int tuple_list_add(TupleList *list, const int *data, size_t length)
{
    if (list == NULL || list->tuples == NULL || (data == NULL && length > 0)) {
        return -1;
    }
    if (list->count >= list->capacity) {
        return -1;
    }
    if (length > 0 && length > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    list->tuples[list->count].data = NULL;
    list->tuples[list->count].length = length;
    if (length > 0) {
        size_t buffer_size = length * sizeof(int);
        list->tuples[list->count].data = malloc(buffer_size);
        if (list->tuples[list->count].data == NULL) {
            list->tuples[list->count].length = 0;
            return -1;
        }
        memcpy(list->tuples[list->count].data, data, buffer_size);
    }
    list->count++;
    return 0;
}

size_t remove_tuples_of_length(TupleList *list, size_t k)
{
    if (list == NULL || list->tuples == NULL) {
        return 0;
    }

    size_t write_index = 0;
    size_t removed = 0;
    size_t old_count = list->count;

    for (size_t i = 0; i < old_count; i++) {
        if (list->tuples[i].length == k) {
            free(list->tuples[i].data);
            list->tuples[i].data = NULL;
            list->tuples[i].length = 0;
            removed++;
        } else {
            if (write_index != i) {
                list->tuples[write_index] = list->tuples[i];
                list->tuples[i].data = NULL;
                list->tuples[i].length = 0;
            }
            write_index++;
        }
    }
    list->count = write_index;
    return removed;
}

static void print_tuples(const TupleList *list)
{
    if (list == NULL || list->tuples == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].length; j++) {
            printf("%d", list->tuples[i].data[j]);
            if (j + 1 < list->tuples[i].length) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1 < list->count) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void)
{
    TupleList list;
    size_t k;
    size_t removed;

    static const int t1[] = {1, 2};
    static const int t2[] = {3, 4, 5};
    static const int t3[] = {6};
    static const int t4[] = {7, 8};
    static const int t5[] = {9, 10, 11, 12};

    if (tuple_list_init(&list, 8) != 0) {
        fprintf(stderr, "Failed to initialize tuple list\n");
        return EXIT_FAILURE;
    }

    if (tuple_list_add(&list, t1, sizeof(t1) / sizeof(t1[0])) != 0 ||
        tuple_list_add(&list, t2, sizeof(t2) / sizeof(t2[0])) != 0 ||
        tuple_list_add(&list, t3, sizeof(t3) / sizeof(t3[0])) != 0 ||
        tuple_list_add(&list, t4, sizeof(t4) / sizeof(t4[0])) != 0 ||
        tuple_list_add(&list, t5, sizeof(t5) / sizeof(t5[0])) != 0) {
        fprintf(stderr, "Failed to add tuple\n");
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    printf("Before removal:\n");
    print_tuples(&list);

    k = 2;
    removed = remove_tuples_of_length(&list, k);
    printf("Removed %zu tuple(s) of length %zu\n", removed, k);

    printf("After removal:\n");
    print_tuples(&list);

    tuple_list_free(&list);
    return EXIT_SUCCESS;
}