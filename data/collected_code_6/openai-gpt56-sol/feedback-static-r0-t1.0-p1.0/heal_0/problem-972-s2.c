#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t size;
} Tuple;

typedef struct {
    Tuple first;
    Tuple second;
} NestedTuple;

static int copy_tuple(Tuple *destination, const Tuple *source)
{
    if (destination == NULL || source == NULL ||
        (source->size > 0 && source->items == NULL)) {
        return 0;
    }

    destination->items = NULL;
    destination->size = 0;

    if (source->size == 0) {
        return 1;
    }

    if (source->size > SIZE_MAX / sizeof(*source->items)) {
        return 0;
    }

    destination->items = malloc(source->size * sizeof(*source->items));
    if (destination->items == NULL) {
        return 0;
    }

    for (size_t i = 0; i < source->size; ++i) {
        destination->items[i] = source->items[i];
    }

    destination->size = source->size;
    return 1;
}

static void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        tuple->items = NULL;
        tuple->size = 0;
    }
}

static int concatenate_to_nested(const Tuple *first, const Tuple *second,
                                 NestedTuple *result)
{
    if (first == NULL || second == NULL || result == NULL) {
        return 0;
    }

    result->first.items = NULL;
    result->first.size = 0;
    result->second.items = NULL;
    result->second.size = 0;

    if (!copy_tuple(&result->first, first)) {
        return 0;
    }

    if (!copy_tuple(&result->second, second)) {
        free_tuple(&result->first);
        return 0;
    }

    return 1;
}

static void free_nested_tuple(NestedTuple *tuple)
{
    if (tuple != NULL) {
        free_tuple(&tuple->first);
        free_tuple(&tuple->second);
    }
}

static void print_tuple(const Tuple *tuple)
{
    putchar('(');

    for (size_t i = 0; i < tuple->size; ++i) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", tuple->items[i]);
    }

    putchar(')');
}

int main(void)
{
    int first_items[] = {1, 2, 3};
    int second_items[] = {4, 5};
    const Tuple first = {
        first_items,
        sizeof(first_items) / sizeof(first_items[0])
    };
    const Tuple second = {
        second_items,
        sizeof(second_items) / sizeof(second_items[0])
    };
    NestedTuple result;

    if (!concatenate_to_nested(&first, &second, &result)) {
        fputs("Failed to create nested tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');
    print_tuple(&result.first);
    printf(", ");
    print_tuple(&result.second);
    printf(")\n");

    free_nested_tuple(&result);
    return EXIT_SUCCESS;
}