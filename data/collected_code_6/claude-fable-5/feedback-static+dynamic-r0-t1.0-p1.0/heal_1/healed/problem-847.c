#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    size_t bytes;

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

    if (tuple->element->items == NULL) {
        free(copy);
        return NULL;
    }

    if (copy->size > SIZE_MAX / sizeof(int)) {
        free(copy);
        return NULL;
    }

    bytes = copy->size * sizeof(int);

    copy->items = malloc(bytes);
    if (copy->items == NULL) {
        free(copy);
        return NULL;
    }

    memcpy(copy->items, tuple->element->items, bytes);

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
    size_t bytes;
    size_t i;

    if (count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Size overflow\n");
        return EXIT_FAILURE;
    }

    bytes = count * sizeof(int);

    List original;
    original.items = malloc(bytes);
    if (original.items == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(original.items, data, bytes);
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