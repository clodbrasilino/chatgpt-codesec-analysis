#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
} Tuple;

int tuple_size(const Tuple *tuple, size_t *result)
{
    if (tuple == NULL || result == NULL) {
        return -1;
    }

    *result = tuple->size;
    return 0;
}

int main(void)
{
    const int elements[] = {10, 20, 30, 40};
    const Tuple tuple = {
        .size = sizeof(elements) / sizeof(elements[0])
    };
    size_t size = 0U;

    if (tuple_size(&tuple, &size) != 0) {
        fputs("Failed to determine tuple size.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", size) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}