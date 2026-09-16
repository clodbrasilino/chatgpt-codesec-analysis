#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEMENT_INTEGER,
    ELEMENT_TUPLE
} ElementType;

typedef struct {
    ElementType type;
} Element;

static size_t count_until_tuple(const Element *list, size_t length)
{
    size_t count = 0;

    if (list == NULL) {
        return 0;
    }

    while (count < length && list[count].type != ELEMENT_TUPLE) {
        ++count;
    }

    return count;
}

int main(void)
{
    const Element list[] = {
        { .type = ELEMENT_INTEGER },
        { .type = ELEMENT_INTEGER },
        { .type = ELEMENT_TUPLE },
        { .type = ELEMENT_INTEGER }
    };
    const size_t length = sizeof list / sizeof list[0];
    const size_t count = count_until_tuple(list, length);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}