#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
} Tuple;

size_t tuple_size(const Tuple *tuple)
{
    return tuple != NULL ? tuple->size : 0;
}

int main(void)
{
    Tuple tuple = {
        .size = 3
    };

    if (printf("%zu\n", tuple_size(&tuple)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}