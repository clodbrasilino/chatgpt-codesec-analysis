#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Tuple Tuple;

typedef enum {
    ELEMENT_INTEGER,
    ELEMENT_STRING,
    ELEMENT_TUPLE
} ElementType;

typedef struct {
    ElementType type;
    union {
        long integer;
        char *string;
        Tuple *tuple;
    } value;
} Element;

struct Tuple {
    Element *elements;
    size_t length;
};

typedef struct {
    ElementType type;
    union {
        long integer;
        const char *string;
    } value;
} SearchValue;

static int count_frequency(const Tuple *tuple, const SearchValue *target,
                           size_t *count)
{
    size_t i;

    if (tuple == NULL || target == NULL || count == NULL) {
        return -1;
    }

    if (target->type != ELEMENT_INTEGER && target->type != ELEMENT_STRING) {
        return -1;
    }

    if (target->type == ELEMENT_STRING && target->value.string == NULL) {
        return -1;
    }

    if (tuple->length > 0U && tuple->elements == NULL) {
        return -1;
    }

    for (i = 0U; i < tuple->length; ++i) {
        const Element *element = &tuple->elements[i];

        switch (element->type) {
            case ELEMENT_INTEGER:
                if (target->type == ELEMENT_INTEGER &&
                    element->value.integer == target->value.integer) {
                    if (*count == SIZE_MAX) {
                        return -1;
                    }
                    ++(*count);
                }
                break;

            case ELEMENT_STRING:
                if (element->value.string == NULL) {
                    return -1;
                }
                if (target->type == ELEMENT_STRING &&
                    strcmp(element->value.string, target->value.string) == 0) {
                    if (*count == SIZE_MAX) {
                        return -1;
                    }
                    ++(*count);
                }
                break;

            case ELEMENT_TUPLE:
                if (element->value.tuple == NULL ||
                    count_frequency(element->value.tuple, target, count) != 0) {
                    return -1;
                }
                break;

            default:
                return -1;
        }
    }

    return 0;
}

int main(void)
{
    Element inner_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 2L },
        { .type = ELEMENT_STRING, .value.string = "apple" },
        { .type = ELEMENT_INTEGER, .value.integer = 2L }
    };
    Tuple inner = {
        .elements = inner_elements,
        .length = sizeof(inner_elements) / sizeof(inner_elements[0])
    };
    Element outer_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 2L },
        { .type = ELEMENT_STRING, .value.string = "banana" },
        { .type = ELEMENT_TUPLE, .value.tuple = &inner },
        { .type = ELEMENT_STRING, .value.string = "apple" }
    };
    Tuple outer = {
        .elements = outer_elements,
        .length = sizeof(outer_elements) / sizeof(outer_elements[0])
    };
    SearchValue target = {
        .type = ELEMENT_STRING,
        .value.string = "apple"
    };
    size_t count = 0U;

    errno = 0;
    if (count_frequency(&outer, &target, &count) != 0) {
        fputs("Failed to count element frequency.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}