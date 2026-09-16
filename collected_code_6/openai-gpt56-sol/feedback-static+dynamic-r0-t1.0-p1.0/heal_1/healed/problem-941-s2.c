#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEMENT_INTEGER,
    ELEMENT_TUPLE
} ElementType;

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    ElementType type;
    union {
        int integer;
        Tuple tuple;
    } value;
} Element;

static size_t count_until_tuple(const Element *list, size_t length, Tuple *tuple)
{
    size_t count = 0;

    if (list == NULL) {
        return 0;
    }

    while (count < length) {
        if (list[count].type == ELEMENT_TUPLE) {
            if (tuple != NULL) {
                tuple->first = list[count].value.tuple.first;
                tuple->second = list[count].value.tuple.second;
            }
            break;
        }
        ++count;
    }

    return count;
}

int main(void)
{
    const Element list[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 10 },
        { .type = ELEMENT_INTEGER, .value.integer = 20 },
        { .type = ELEMENT_TUPLE, .value.tuple = { .first = 30, .second = 40 } },
        { .type = ELEMENT_INTEGER, .value.integer = 50 }
    };
    const size_t length = sizeof(list) / sizeof(list[0]);
    Tuple tuple = { 0, 0 };
    const size_t count = count_until_tuple(list, length, &tuple);

    if (count < length) {
        if (printf("%zu (%d, %d)\n", count, tuple.first, tuple.second) < 0) {
            return EXIT_FAILURE;
        }
    } else if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}