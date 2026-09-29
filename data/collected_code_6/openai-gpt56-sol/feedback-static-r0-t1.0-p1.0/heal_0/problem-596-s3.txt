#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const void *data;
    size_t size;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

static size_t tuple_size(const Tuple *tuple)
{
    return tuple == NULL ? 0U : tuple->count;
}

int main(void)
{
    Tuple tuple = {0};

    tuple.count = 3U;
    tuple.elements = calloc(tuple.count, sizeof(*tuple.elements));
    if (tuple.elements == NULL) {
        fprintf(stderr, "Failed to allocate tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", tuple_size(&tuple));

    free(tuple.elements);
    tuple.elements = NULL;
    tuple.count = 0U;

    return EXIT_SUCCESS;
}