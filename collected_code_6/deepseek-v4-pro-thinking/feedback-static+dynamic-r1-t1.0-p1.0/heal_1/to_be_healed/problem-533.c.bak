#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum data_type {
    DATA_INT,
    DATA_DOUBLE,
    DATA_STRING
} data_type_t;

typedef struct tuple_element {
    data_type_t type;
    union {
        int int_value;
        double double_value;
        char *string_value;
    } value;
} tuple_element_t;

typedef struct tuple {
    tuple_element_t *items;
    size_t size;
    size_t capacity;
} tuple_t;

static int tuple_init(tuple_t *tuple) {
    if (tuple == NULL) return -1;
    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
    return 0;
}

static void tuple_element_clear(tuple_element_t *element) {
    if (element == NULL) return;
    if (element->type == DATA_STRING && element->value.string_value != NULL) {
        free(element->value.string_value);
        element->value.string_value = NULL;
    }
}

static void tuple_free(tuple_t *tuple) {
    if (tuple == NULL) return;
    for (size_t i = 0; i < tuple->size; ++i) {
        tuple_element_clear(&tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

static int tuple_reserve(tuple_t *tuple, size_t needed) {
    if (tuple == NULL) return -1;
    if (needed <= tuple->capacity) return 0;
    size_t new_capacity = tuple->capacity == 0 ? 4 : tuple->capacity;
    while (new_capacity < needed) {
        if (new_capacity > SIZE_MAX / 2) return -1;
        new_capacity *= 2;
    }
    /* Possible weaknesses found:
     *  indirection requires pointer operand ('size_t' (aka 'unsigned long') invalid)
     *  invalid type argument of unary '*' (have 'size_t' {aka 'long unsigned int'})
     */
    if (new_capacity > SIZE_MAX / sizeof(*new_capacity)) return -1;
    tuple_element_t *new_items = realloc(tuple->items, new_capacity * sizeof(*new_items));
    if (new_items == NULL) return -1;
    tuple->items = new_items;
    tuple->capacity = new_capacity;
    return 0;
}

static int tuple_push_int(tuple_t *tuple, int value) {
    if (tuple == NULL || tuple->size == SIZE_MAX) return -1;
    if (tuple_reserve(tuple, tuple->size + 1) != 0) return -1;
    tuple->items[tuple->size].type = DATA_INT;
    tuple->items[tuple->size].value.int_value = value;
    ++tuple->size;
    return 0;
}

static int tuple_push_double(tuple_t *tuple, double value) {
    if (tuple == NULL || tuple->size == SIZE_MAX) return -1;
    if (tuple_reserve(tuple, tuple->size + 1) != 0) return -1;
    tuple->items[tuple->size].type = DATA_DOUBLE;
    tuple->items[tuple->size].value.double_value = value;
    ++tuple->size;
    return 0;
}

static int tuple_push_string(tuple_t *tuple, const char *value) {
    if (tuple == NULL || value == NULL || tuple->size == SIZE_MAX) return -1;
    size_t length = strlen(value);
    char *copy = malloc(length + 1);
    if (copy == NULL) return -1;
    memcpy(copy, value, length + 1);
    if (tuple_reserve(tuple, tuple->size + 1) != 0) {
        free(copy);
        return -1;
    }
    tuple->items[tuple->size].type = DATA_STRING;
    tuple->items[tuple->size].value.string_value = copy;
    ++tuple->size;
    return 0;
}

int tuple_remove_type(tuple_t *tuple, data_type_t type) {
    if (tuple == NULL) return -1;
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < tuple->size; ++read_index) {
        if (tuple->items[read_index].type == type) {
            tuple_element_clear(&tuple->items[read_index]);
        } else {
            if (write_index != read_index) {
                tuple->items[write_index] = tuple->items[read_index];
                if (tuple->items[read_index].type == DATA_STRING) {
                    tuple->items[read_index].value.string_value = NULL;
                }
            }
            ++write_index;
        }
    }
    tuple->size = write_index;
    return 0;
}

int main(void) {
    tuple_t tuple;
    if (tuple_init(&tuple) != 0) return EXIT_FAILURE;

    if (tuple_push_int(&tuple, 42) != 0) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }
    if (tuple_push_double(&tuple, 3.14) != 0) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }
    if (tuple_push_string(&tuple, "hello") != 0) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }
    if (tuple_push_int(&tuple, 7) != 0) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }
    if (tuple_push_string(&tuple, "world") != 0) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }

    if (tuple_remove_type(&tuple, DATA_STRING) != 0) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple.size; ++i) {
        switch (tuple.items[i].type) {
            case DATA_INT:
                printf("%d\n", tuple.items[i].value.int_value);
                break;
            case DATA_DOUBLE:
                printf("%f\n", tuple.items[i].value.double_value);
                break;
            case DATA_STRING:
                printf("%s\n", tuple.items[i].value.string_value);
                break;
            default:
                break;
        }
    }

    tuple_free(&tuple);
    return EXIT_SUCCESS;
}