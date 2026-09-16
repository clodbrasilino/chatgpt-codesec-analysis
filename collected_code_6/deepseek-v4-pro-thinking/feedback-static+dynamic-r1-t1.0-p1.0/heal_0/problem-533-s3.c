#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int int_value;
        float float_value;
        double double_value;
        char char_value;
    } data;
} TupleElement;

typedef struct {
    TupleElement *items;
    size_t size;
    size_t capacity;
} Tuple;

static int tuple_reserve(Tuple *tuple, size_t new_capacity) {
    TupleElement *new_items;

    if (tuple == NULL) {
        return -1;
    }
    if (new_capacity <= tuple->capacity) {
        return 0;
    }
    if (new_capacity > SIZE_MAX / sizeof(TupleElement)) {
        return -1;
    }

    new_items = realloc(tuple->items, new_capacity * sizeof(TupleElement));
    if (new_items == NULL) {
        return -1;
    }

    tuple->items = new_items;
    tuple->capacity = new_capacity;
    return 0;
}

int tuple_init(Tuple *tuple, size_t initial_capacity) {
    if (tuple == NULL) {
        return -1;
    }

    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;

    if (initial_capacity == 0 || initial_capacity > SIZE_MAX / sizeof(TupleElement)) {
        return -1;
    }

    tuple->items = malloc(initial_capacity * sizeof(TupleElement));
    if (tuple->items == NULL) {
        return -1;
    }

    tuple->capacity = initial_capacity;
    return 0;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

static int tuple_add_element(Tuple *tuple, DataType type, const void *value) {
    if (tuple == NULL || tuple->items == NULL || tuple->capacity == 0 || value == NULL) {
        return -1;
    }
    if (type < TYPE_INT || type > TYPE_CHAR) {
        return -1;
    }

    if (tuple->size == tuple->capacity) {
        size_t new_capacity = tuple->capacity * 2;

        if (new_capacity < tuple->capacity) {
            return -1;
        }
        if (tuple_reserve(tuple, new_capacity) != 0) {
            return -1;
        }
    }

    switch (type) {
        case TYPE_INT:
            tuple->items[tuple->size].data.int_value = *(const int *)value;
            break;
        case TYPE_FLOAT:
            tuple->items[tuple->size].data.float_value = *(const float *)value;
            break;
        case TYPE_DOUBLE:
            tuple->items[tuple->size].data.double_value = *(const double *)value;
            break;
        case TYPE_CHAR:
            tuple->items[tuple->size].data.char_value = *(const char *)value;
            break;
        default:
            return -1;
    }

    tuple->items[tuple->size].type = type;
    tuple->size++;
    return 0;
}

int tuple_add_int(Tuple *tuple, int value) {
    return tuple_add_element(tuple, TYPE_INT, &value);
}

int tuple_add_float(Tuple *tuple, float value) {
    return tuple_add_element(tuple, TYPE_FLOAT, &value);
}

int tuple_add_double(Tuple *tuple, double value) {
    return tuple_add_element(tuple, TYPE_DOUBLE, &value);
}

int tuple_add_char(Tuple *tuple, char value) {
    return tuple_add_element(tuple, TYPE_CHAR, &value);
}

int tuple_remove_type(Tuple *tuple, DataType type) {
    size_t read_index;
    size_t write_index;

    if (tuple == NULL) {
        return -1;
    }
    if (tuple->items == NULL && tuple->size != 0) {
        return -1;
    }
    if (type < TYPE_INT || type > TYPE_CHAR) {
        return -1;
    }

    write_index = 0;
    for (read_index = 0; read_index < tuple->size; read_index++) {
        if (tuple->items[read_index].type != type) {
            if (write_index != read_index) {
                tuple->items[write_index] = tuple->items[read_index];
            }
            write_index++;
        }
    }

    tuple->size = write_index;
    return 0;
}

static void tuple_print(const Tuple *tuple) {
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->size; i++) {
        switch (tuple->items[i].type) {
            case TYPE_INT:
                printf("%d ", tuple->items[i].data.int_value);
                break;
            case TYPE_FLOAT:
                printf("%f ", tuple->items[i].data.float_value);
                break;
            case TYPE_DOUBLE:
                printf("%f ", tuple->items[i].data.double_value);
                break;
            case TYPE_CHAR:
                printf("%c ", tuple->items[i].data.char_value);
                break;
            default:
                break;
        }
    }
    printf("\n");
}

int main(void) {
    Tuple tuple;

    if (tuple_init(&tuple, 4) != 0) {
        return 1;
    }

    if (tuple_add_int(&tuple, 10) != 0 ||
        tuple_add_float(&tuple, 2.5f) != 0 ||
        tuple_add_double(&tuple, 3.14159) != 0 ||
        tuple_add_char(&tuple, 'A') != 0 ||
        tuple_add_int(&tuple, 20) != 0 ||
        tuple_add_float(&tuple, 1.25f) != 0) {
        tuple_free(&tuple);
        return 1;
    }

    printf("Before removal:\n");
    tuple_print(&tuple);

    if (tuple_remove_type(&tuple, TYPE_INT) != 0) {
        tuple_free(&tuple);
        return 1;
    }

    printf("After removal:\n");
    tuple_print(&tuple);

    tuple_free(&tuple);
    return 0;
}