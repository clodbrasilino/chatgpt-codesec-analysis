#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    ELEMENT_INTEGER,
    ELEMENT_TUPLE
} ElementType;

typedef struct Tuple Tuple;

typedef struct {
    ElementType type;
    union {
        int integer;
        Tuple *tuple;
    } value;
} Element;

struct Tuple {
    Element *elements;
    size_t count;
};

typedef struct {
    int *values;
    size_t count;
    size_t capacity;
} IntegerArray;

static bool append_integer(IntegerArray *array, int value)
{
    if (array == NULL) {
        return false;
    }

    if (array->count == array->capacity) {
        size_t new_capacity;
        int *new_values;

        if (array->capacity > SIZE_MAX / 2U) {
            return false;
        }

        new_capacity = array->capacity == 0U ? 8U : array->capacity * 2U;

        if (new_capacity > SIZE_MAX / sizeof(*array->values)) {
            return false;
        }

        new_values = realloc(array->values,
                             new_capacity * sizeof(*array->values));
        if (new_values == NULL) {
            return false;
        }

        array->values = new_values;
        array->capacity = new_capacity;
    }

    array->values[array->count++] = value;
    return true;
}

static bool extract_even_elements(const Tuple *tuple, IntegerArray *result)
{
    size_t index;

    if (tuple == NULL || result == NULL ||
        (tuple->count != 0U && tuple->elements == NULL)) {
        return false;
    }

    for (index = 0U; index < tuple->count; ++index) {
        const Element *element = &tuple->elements[index];

        switch (element->type) {
            case ELEMENT_INTEGER:
                if (element->value.integer % 2 == 0 &&
                    !append_integer(result, element->value.integer)) {
                    return false;
                }
                break;

            case ELEMENT_TUPLE:
                if (element->value.tuple == NULL ||
                    !extract_even_elements(element->value.tuple, result)) {
                    return false;
                }
                break;

            default:
                return false;
        }
    }

    return true;
}

int main(void)
{
    Element inner_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 3 },
        { .type = ELEMENT_INTEGER, .value.integer = 4 },
        { .type = ELEMENT_INTEGER, .value.integer = 6 }
    };
    Tuple inner_tuple = {
        .elements = inner_elements,
        .count = sizeof(inner_elements) / sizeof(inner_elements[0])
    };
    Element outer_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 1 },
        { .type = ELEMENT_INTEGER, .value.integer = 2 },
        { .type = ELEMENT_TUPLE, .value.tuple = &inner_tuple },
        { .type = ELEMENT_INTEGER, .value.integer = 8 }
    };
    Tuple outer_tuple = {
        .elements = outer_elements,
        .count = sizeof(outer_elements) / sizeof(outer_elements[0])
    };
    IntegerArray result = { NULL, 0U, 0U };
    size_t index;

    if (!extract_even_elements(&outer_tuple, &result)) {
        free(result.values);
        fputs("Failed to extract even elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < result.count; ++index) {
        if (printf("%d%s",
                   result.values[index],
                   index + 1U == result.count ? "\n" : " ") < 0) {
            free(result.values);
            return EXIT_FAILURE;
        }
    }

    free(result.values);
    return EXIT_SUCCESS;
}