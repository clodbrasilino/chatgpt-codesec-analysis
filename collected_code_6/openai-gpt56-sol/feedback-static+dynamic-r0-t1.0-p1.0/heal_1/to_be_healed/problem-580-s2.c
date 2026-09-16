#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

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

static bool append_even(int **values, size_t *count, size_t *capacity, int value)
{
    int *resized;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (*count == *capacity) {
        if (*capacity > SIZE_MAX / 2U) {
            return false;
        }

        new_capacity = (*capacity == 0U) ? 8U : *capacity * 2U;

        if (new_capacity > SIZE_MAX / sizeof(**values)) {
            return false;
        }

        resized = realloc(*values, new_capacity * sizeof(**values));
        if (resized == NULL) {
            return false;
        }

        *values = resized;
        *capacity = new_capacity;
    }

    (*values)[*count] = value;
    ++(*count);
    return true;
}

static bool extract_even_recursive(const Tuple *tuple, int **values,
                                   size_t *count, size_t *capacity)
{
    size_t i;

    if (tuple == NULL || (tuple->count > 0U && tuple->elements == NULL)) {
        return false;
    }

    for (i = 0U; i < tuple->count; ++i) {
        const Element *element = &tuple->elements[i];

        switch (element->type) {
            case ELEMENT_INTEGER:
                if (element->value.integer % 2 == 0 &&
                    !append_even(values, count, capacity,
                                 element->value.integer)) {
                    return false;
                }
                break;

            case ELEMENT_TUPLE:
                if (!extract_even_recursive(element->value.tuple, values,
                                            count, capacity)) {
                    return false;
                }
                break;

            default:
                return false;
        }
    }

    return true;
}

static bool extract_even_elements(const Tuple *tuple, int **result,
                                  size_t *result_count)
{
    size_t capacity = 0U;

    if (result == NULL || result_count == NULL) {
        return false;
    }

    *result = NULL;
    *result_count = 0U;

    if (!extract_even_recursive(tuple, result, result_count, &capacity)) {
        free(*result);
        *result = NULL;
        *result_count = 0U;
        return false;
    }

    return true;
}

int main(void)
{
    Element inner_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 2 },
        { .type = ELEMENT_INTEGER, .value.integer = 3 },
        { .type = ELEMENT_INTEGER, .value.integer = 8 }
    };
    Tuple inner = {
        .elements = inner_elements,
        .count = sizeof(inner_elements) / sizeof(inner_elements[0])
    };

    Element deeper_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 10 },
        { .type = ELEMENT_INTEGER, .value.integer = 11 }
    };
    Tuple deeper = {
        .elements = deeper_elements,
        .count = sizeof(deeper_elements) / sizeof(deeper_elements[0])
    };

    Element middle_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 5 },
        { .type = ELEMENT_TUPLE, .value.tuple = &deeper },
        { .type = ELEMENT_INTEGER, .value.integer = 12 }
    };
    Tuple middle = {
        .elements = middle_elements,
        .count = sizeof(middle_elements) / sizeof(middle_elements[0])
    };

    Element root_elements[] = {
        { .type = ELEMENT_INTEGER, .value.integer = 1 },
        { .type = ELEMENT_TUPLE, .value.tuple = &inner },
        { .type = ELEMENT_INTEGER, .value.integer = 4 },
        { .type = ELEMENT_TUPLE, .value.tuple = &middle },
        { .type = ELEMENT_INTEGER, .value.integer = 7 }
    };
    Tuple root = {
        .elements = root_elements,
        .count = sizeof(root_elements) / sizeof(root_elements[0])
    };

    int *even_values = NULL;
    size_t even_count = 0U;
    size_t i;

    if (!extract_even_elements(&root, &even_values, &even_count)) {
        fputs("Failed to extract even elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < even_count; ++i) {
        if (printf("%d%s", even_values[i],
                   (i + 1U == even_count) ? "\n" : " ") < 0) {
            free(even_values);
            return EXIT_FAILURE;
        }
    }

    free(even_values);
    return EXIT_SUCCESS;
}