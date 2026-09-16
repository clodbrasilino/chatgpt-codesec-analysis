#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

int init_list(TupleList *list, size_t initial_capacity)
{
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }

    list->data = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }

    list->size = 0;
    list->capacity = initial_capacity;
    return 0;
}

int add_tuple(TupleList *list, Tuple tuple)
{
    if (list == NULL || list->data == NULL) {
        return -1;
    }

    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }

    list->data[list->size] = tuple;
    list->size++;
    return 0;
}

void free_list(TupleList *list)
{
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int main(void)
{
    TupleList list;
    Tuple tuples[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (init_list(&list, 2) != 0) {
        fprintf(stderr, "Error: failed to initialize list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; i++) {
        if (add_tuple(&list, tuples[i]) != 0) {
            fprintf(stderr, "Error: failed to add tuple\n");
            free_list(&list);
            return EXIT_FAILURE;
        }
    }

    printf("List contents:\n");
    for (i = 0; i < list.size; i++) {
        printf("(%d, %d)\n", list.data[i].first, list.data[i].second);
    }

    free_list(&list);
    return EXIT_SUCCESS;
}