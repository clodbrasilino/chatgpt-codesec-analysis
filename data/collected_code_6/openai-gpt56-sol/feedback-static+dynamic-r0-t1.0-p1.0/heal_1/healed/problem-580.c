#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

static int append_even(int **values, size_t *count, size_t *capacity, int value)
{
    if (*count == *capacity) {
        size_t new_capacity;
        int *resized;

        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **values) {
            return 0;
        }

        resized = realloc(*values, new_capacity * sizeof **values);
        if (resized == NULL) {
            return 0;
        }

        *values = resized;
        *capacity = new_capacity;
    }

    (*values)[*count] = value;
    ++*count;
    return 1;
}

static int collect_even(const Tuple *tuple, int **values, size_t *count,
                        size_t *capacity)
{
    size_t i;

    if (tuple == NULL || (tuple->count != 0 && tuple->elements == NULL)) {
        return 0;
    }

    for (i = 0; i < tuple->count; ++i) {
        const Element *element = &tuple->elements[i];

        switch (element->type) {
        case ELEMENT_INTEGER:
            if (element->value.integer % 2 == 0 &&
                !append_even(values, count, capacity,
                             element->value.integer)) {
                return 0;
            }
            break;

        case ELEMENT_TUPLE:
            if (element->value.tuple == NULL ||
                !collect_even(element->value.tuple, values, count,
                              capacity)) {
                return 0;
            }
            break;

        default:
            return 0;
        }
    }

    return 1;
}

static int extract_even(const Tuple *tuple, int **result, size_t *result_count)
{
    size_t capacity = 0;

    if (result == NULL || result_count == NULL) {
        return 0;
    }

    *result = NULL;
    *result_count = 0;

    if (!collect_even(tuple, result, result_count, &capacity)) {
        free(*result);
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    return 1;
}

int main(void)
{
    Element inner_elements[] = {
        {ELEMENT_INTEGER, {.integer = 3}},
        {ELEMENT_INTEGER, {.integer = 4}},
        {ELEMENT_INTEGER, {.integer = 6}}
    };
    Tuple inner = {
        inner_elements,
        sizeof inner_elements / sizeof inner_elements[0]
    };

    Element middle_elements[] = {
        {ELEMENT_INTEGER, {.integer = 2}},
        {ELEMENT_TUPLE, {.tuple = &inner}},
        {ELEMENT_INTEGER, {.integer = 7}}
    };
    Tuple middle = {
        middle_elements,
        sizeof middle_elements / sizeof middle_elements[0]
    };

    Element outer_elements[] = {
        {ELEMENT_INTEGER, {.integer = 1}},
        {ELEMENT_TUPLE, {.tuple = &middle}},
        {ELEMENT_INTEGER, {.integer = 8}},
        {ELEMENT_INTEGER, {.integer = 9}}
    };
    Tuple outer = {
        outer_elements,
        sizeof outer_elements / sizeof outer_elements[0]
    };

    int *even_values = NULL;
    size_t even_count = 0;
    size_t i;

    if (!extract_even(&outer, &even_values, &even_count)) {
        fputs("Failed to extract even elements\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < even_count; ++i) {
        if (printf("%d%s", even_values[i],
                   i + 1 < even_count ? " " : "\n") < 0) {
            free(even_values);
            return EXIT_FAILURE;
        }
    }

    if (even_count == 0 && putchar('\n') == EOF) {
        free(even_values);
        return EXIT_FAILURE;
    }

    free(even_values);
    return EXIT_SUCCESS;
}