#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    int *items;
} Tuple;

static Tuple *clone_tuple(const Tuple *source)
{
    Tuple *clone;

    if (source == NULL || (source->size > 0 && source->items == NULL)) {
        return NULL;
    }

    clone = malloc(sizeof(*clone));
    if (clone == NULL) {
        return NULL;
    }

    clone->size = source->size;
    clone->items = NULL;

    if (source->size > 0) {
        if (source->size > SIZE_MAX / sizeof(*source->items)) {
            free(clone);
            return NULL;
        }

        clone->items = malloc(source->size * sizeof(*clone->items));
        if (clone->items == NULL) {
            free(clone);
            return NULL;
        }

        for (size_t i = 0; i < source->size; ++i) {
            clone->items[i] = source->items[i];
        }
    }

    return clone;
}

static void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        free(tuple);
    }
}

int main(void)
{
    int values[] = {1, 2, 3, 4};
    Tuple original = {
        sizeof(values) / sizeof(values[0]),
        values
    };
    Tuple *clone = clone_tuple(&original);

    if (clone == NULL) {
        fputs("Failed to clone tuple\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < clone->size; ++i) {
        if (printf("%s%d", i == 0 ? "(" : ", ", clone->items[i]) < 0) {
            free_tuple(clone);
            return EXIT_FAILURE;
        }
    }

    if (puts(")") == EOF) {
        free_tuple(clone);
        return EXIT_FAILURE;
    }

    free_tuple(clone);
    return EXIT_SUCCESS;
}