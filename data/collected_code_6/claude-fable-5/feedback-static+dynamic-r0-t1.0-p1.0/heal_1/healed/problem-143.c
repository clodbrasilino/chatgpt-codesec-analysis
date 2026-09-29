#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEMENT_INT,
    ELEMENT_STRING,
    ELEMENT_LIST
} ElementType;

typedef struct {
    ElementType type;
    union {
        int int_value;
        const char *string_value;
        struct {
            const int *items;
            size_t count;
        } list_value;
    } data;
} Element;

typedef struct {
    const Element *elements;
    size_t count;
} Tuple;

static int count_lists(const Tuple *tuple, size_t *result)
{
    size_t i;
    size_t total;

    if (tuple == NULL || result == NULL) {
        return -1;
    }

    if (tuple->count > 0U && tuple->elements == NULL) {
        return -1;
    }

    total = 0U;
    for (i = 0U; i < tuple->count; i++) {
        if (tuple->elements[i].type == ELEMENT_LIST) {
            total++;
        }
    }

    *result = total;
    return 0;
}

static int print_elements(const Tuple *tuple)
{
    size_t i;
    size_t j;

    if (tuple == NULL) {
        return -1;
    }

    if (tuple->count > 0U && tuple->elements == NULL) {
        return -1;
    }

    for (i = 0U; i < tuple->count; i++) {
        const Element *element = &tuple->elements[i];

        switch (element->type) {
        case ELEMENT_INT:
            if (printf("Element %zu: int = %d\n", i,
                       element->data.int_value) < 0) {
                return -1;
            }
            break;
        case ELEMENT_STRING:
            if (element->data.string_value == NULL) {
                return -1;
            }
            if (printf("Element %zu: string = %s\n", i,
                       element->data.string_value) < 0) {
                return -1;
            }
            break;
        case ELEMENT_LIST:
            if (element->data.list_value.count > 0U &&
                element->data.list_value.items == NULL) {
                return -1;
            }
            if (printf("Element %zu: list =", i) < 0) {
                return -1;
            }
            for (j = 0U; j < element->data.list_value.count; j++) {
                if (printf(" %d",
                           element->data.list_value.items[j]) < 0) {
                    return -1;
                }
            }
            if (printf("\n") < 0) {
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
    static const int list_a[] = {1, 2, 3};
    static const int list_b[] = {4, 5};
    static const int list_c[] = {6};

    static const Element elements[] = {
        { ELEMENT_LIST, { .list_value = { list_a, 3U } } },
        { ELEMENT_INT, { .int_value = 10 } },
        { ELEMENT_LIST, { .list_value = { list_b, 2U } } },
        { ELEMENT_STRING, { .string_value = "hello" } },
        { ELEMENT_LIST, { .list_value = { list_c, 1U } } }
    };

    Tuple tuple;
    size_t result;

    tuple.elements = elements;
    tuple.count = sizeof(elements) / sizeof(elements[0]);

    result = 0U;
    if (count_lists(&tuple, &result) != 0) {
        (void)fprintf(stderr, "Error: invalid tuple input\n");
        return EXIT_FAILURE;
    }

    if (print_elements(&tuple) != 0) {
        (void)fprintf(stderr, "Error: failed to print elements\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of lists in the tuple: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}