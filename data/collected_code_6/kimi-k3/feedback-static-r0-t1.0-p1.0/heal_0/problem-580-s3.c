#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct Element Element;

typedef struct {
    Element *elements;
    size_t count;
    size_t capacity;
} Tuple;

struct Element {
    ElementType type;
    union {
        int int_value;
        Tuple *tuple_value;
    } data;
};

static Tuple *tuple_create(size_t capacity) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->elements = malloc(sizeof(Element) * capacity);
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->count = 0;
    tuple->capacity = capacity;
    return tuple;
}

static void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type == TYPE_TUPLE) {
            tuple_free(tuple->elements[i].data.tuple_value);
        }
    }
    free(tuple->elements);
    free(tuple);
}

static int tuple_add_int(Tuple *tuple, int value) {
    if (tuple == NULL || tuple->count >= tuple->capacity) {
        return -1;
    }
    tuple->elements[tuple->count].type = TYPE_INT;
    tuple->elements[tuple->count].data.int_value = value;
    tuple->count++;
    return 0;
}

static int tuple_add_tuple(Tuple *tuple, Tuple *nested) {
    if (tuple == NULL || nested == NULL || tuple->count >= tuple->capacity) {
        return -1;
    }
    tuple->elements[tuple->count].type = TYPE_TUPLE;
    tuple->elements[tuple->count].data.tuple_value = nested;
    tuple->count++;
    return 0;
}

static int extract_even_recursive(const Tuple *tuple, int *result, size_t *index, size_t max_count) {
    if (tuple == NULL || result == NULL || index == NULL) {
        return -1;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type == TYPE_INT) {
            if (tuple->elements[i].data.int_value % 2 == 0) {
                if (*index >= max_count) {
                    return -1;
                }
                result[*index] = tuple->elements[i].data.int_value;
                (*index)++;
            }
        } else if (tuple->elements[i].type == TYPE_TUPLE) {
            if (extract_even_recursive(tuple->elements[i].data.tuple_value, result, index, max_count) != 0) {
                return -1;
            }
        }
    }
    return 0;
}

static size_t count_ints_recursive(const Tuple *tuple) {
    size_t count = 0;
    if (tuple == NULL) {
        return 0;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].type == TYPE_INT) {
            count++;
        } else if (tuple->elements[i].type == TYPE_TUPLE) {
            count += count_ints_recursive(tuple->elements[i].data.tuple_value);
        }
    }
    return count;
}

int *extract_even_elements(const Tuple *tuple, size_t *result_count) {
    if (tuple == NULL || result_count == NULL) {
        return NULL;
    }
    size_t max_ints = count_ints_recursive(tuple);
    if (max_ints == 0) {
        *result_count = 0;
        return NULL;
    }
    int *result = malloc(sizeof(int) * max_ints);
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }
    size_t index = 0;
    if (extract_even_recursive(tuple, result, &index, max_ints) != 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }
    *result_count = index;
    return result;
}

int main(void) {
    Tuple *root = tuple_create(4);
    if (root == NULL) {
        fprintf(stderr, "Failed to create root tuple\n");
        return EXIT_FAILURE;
    }

    Tuple *nested1 = tuple_create(3);
    if (nested1 == NULL) {
        fprintf(stderr, "Failed to create nested tuple 1\n");
        tuple_free(root);
        return EXIT_FAILURE;
    }

    Tuple *nested2 = tuple_create(2);
    if (nested2 == NULL) {
        fprintf(stderr, "Failed to create nested tuple 2\n");
        tuple_free(nested1);
        tuple_free(root);
        return EXIT_FAILURE;
    }

    if (tuple_add_int(root, 1) != 0 ||
        tuple_add_int(root, 4) != 0 ||
        tuple_add_int(nested1, 7) != 0 ||
        tuple_add_int(nested1, 10) != 0 ||
        tuple_add_int(nested1, 12) != 0 ||
        tuple_add_int(nested2, 3) != 0 ||
        tuple_add_int(nested2, 8) != 0 ||
        tuple_add_tuple(nested1, nested2) != 0 ||
        tuple_add_tuple(root, nested1) != 0 ||
        tuple_add_int(root, 6) != 0) {
        fprintf(stderr, "Failed to build tuple structure\n");
        tuple_free(nested2);
        tuple_free(nested1);
        tuple_free(root);
        return EXIT_FAILURE;
    }

    size_t result_count = 0;
    int *evens = extract_even_elements(root, &result_count);
    if (evens == NULL && result_count > 0) {
        fprintf(stderr, "Failed to extract even elements\n");
        tuple_free(root);
        return EXIT_FAILURE;
    }

    printf("Even elements: ");
    for (size_t i = 0; i < result_count; i++) {
        printf("%d ", evens[i]);
    }
    printf("\n");

    free(evens);
    tuple_free(root);

    return EXIT_SUCCESS;
}