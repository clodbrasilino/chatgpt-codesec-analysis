#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t count;
} Tuple;

static size_t tuple_size(const Tuple *tuple)
{
    return tuple != NULL ? tuple->count : 0U;
}

int main(void)
{
    Tuple tuple = {0U};

    tuple.count = 3U;

    printf("%zu\n", tuple_size(&tuple));

    return EXIT_SUCCESS;
}