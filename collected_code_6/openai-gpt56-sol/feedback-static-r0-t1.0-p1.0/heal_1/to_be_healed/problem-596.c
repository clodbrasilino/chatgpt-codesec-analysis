#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::items' is never used. [unusedStructMember]
     */
    void **items;
    size_t size;
} Tuple;

size_t tuple_size(const Tuple *tuple)
{
    if (tuple == NULL) {
        return 0;
    }

    return tuple->size;
}

int main(void)
{
    int first = 10;
    double second = 20.5;
    const char *third = "example";

    void *items[] = {&first, &second, (void *)third};
    Tuple tuple = {
        .items = items,
        .size = sizeof(items) / sizeof(items[0])
    };

    if (printf("%zu\n", tuple_size(&tuple)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}