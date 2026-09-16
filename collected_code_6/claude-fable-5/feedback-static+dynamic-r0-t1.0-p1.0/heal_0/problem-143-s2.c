#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEM_INT,
    ELEM_STRING,
    ELEM_LIST
} ElementType;

typedef struct {
    ElementType type;
    void *data;
    size_t length;
} Element;

typedef struct {
    Element *elements;
    size_t count;
} Tuple;

static size_t count_lists(const Tuple *tuple)
{
    size_t total;
    size_t i;

    total = 0U;

    if (tuple == NULL) {
        return total;
    }

    if (tuple->elements == NULL) {
        return total;
    }

    for (i = 0U; i < tuple->count; i++) {
        if (tuple->elements[i].type == ELEM_LIST) {
            total++;
        }
    }

    return total;
}

static Tuple *create_tuple(size_t count)
{
    Tuple *tuple;

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = count;
    tuple->elements = NULL;

    if (count > 0U) {
        tuple->elements = (Element *)calloc(count, sizeof(Element));
        if (tuple->elements == NULL) {
            free(tuple);
            return NULL;
        }
    }

    return tuple;
}

static void destroy_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->elements);
    tuple->elements = NULL;
    free(tuple);
}

int main(void)
{
    Tuple *tuple;
    size_t result;
    int list_a[3] = {1, 2, 3};
    int list_b[2] = {4, 5};
    int scalar = 7;

    tuple = create_tuple(4U);
    if (tuple == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuple->elements[0].type = ELEM_LIST;
    tuple->elements[0].data = (void *)list_a;
    tuple->elements[0].length = 3U;

    tuple->elements[1].type = ELEM_INT;
    tuple->elements[1].data = (void *)&scalar;
    tuple->elements[1].length = 1U;

    tuple->elements[2].type = ELEM_LIST;
    tuple->elements[2].data = (void *)list_b;
    tuple->elements[2].length = 2U;

    tuple->elements[3].type = ELEM_STRING;
    tuple->elements[3].data = (void *)"hello";
    tuple->elements[3].length = 5U;

    result = count_lists(tuple);

    if (printf("Number of lists in the tuple: %zu\n", result) < 0) {
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }

    destroy_tuple(tuple);

    return EXIT_SUCCESS;
}