#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t size;
} List;

typedef struct {
    List *element;
} SingletonTuple;

List *copy_list_from_tuple(const SingletonTuple *tuple)
{
    List *copy;

    if (tuple == NULL || tuple->element == NULL) {
        return NULL;
    }

    copy = malloc(sizeof(List));
    if (copy == NULL) {
        return NULL;
    }

    copy->size = tuple->element->size;

    if (copy->size == 0) {
        copy->items = NULL;
        return copy;
    }

    copy->items = malloc(copy->size * sizeof(int));
    if (copy->items == NULL) {
        free(copy);
        return NULL;
    }

    memcpy(copy->items, tuple->element->items, copy->size * sizeof(int));

    return copy;
}

void free_list(List *list)
{
    if (list != NULL) {
        free(list->items);
        free(list);
    }
}

int main(void)
{
    int data[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(data) / sizeof(data[0]);
    size_t i;

    List original;
    original.items = malloc(count * sizeof(int));
    if (original.items == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }
    memcpy(original.items, data, count * sizeof(int));
    original.size = count;

    SingletonTuple tuple;
    tuple.element = &original;

    List *copied = copy_list_from_tuple(&tuple);
    if (copied == NULL) {
        fprintf(stderr, "Copy failed\n");
        free(original.items);
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    for (i = 0; i < original.size; i++) {
        printf("%d ", original.items[i]);
    }
    printf("\n");

    printf("Copied list:   ");
    for (i = 0; i < copied->size; i++) {
        printf("%d ", copied->items[i]);
    }
    printf("\n");

    free(original.items);
    free_list(copied);

    return EXIT_SUCCESS;
}