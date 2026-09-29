#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int int_value;
        float float_value;
        char *string_value;
    } data;
} Element;

typedef struct {
    Element *elements;
    size_t length;
    size_t capacity;
} Tuple;

size_t tuple_remove_by_type(Tuple *tuple, DataType type) {
    if (tuple == NULL || tuple->elements == NULL || tuple->capacity == 0) {
        return 0;
    }

    if (tuple->length > tuple->capacity) {
        tuple->length = tuple->capacity;
    }

    size_t write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < tuple->length; ++read) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= tuple->capacity) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (tuple->elements[read].type == type) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (type == TYPE_STRING && tuple->elements[read].data.string_value != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                free(tuple->elements[read].data.string_value);
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                tuple->elements[read].data.string_value = NULL;
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (write != read) {
                if (write >= tuple->capacity) {
                    break;
                }
                if (tuple->elements[write].type == TYPE_STRING &&
                    tuple->elements[write].data.string_value != NULL) {
                    free(tuple->elements[write].data.string_value);
                }
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                tuple->elements[write] = tuple->elements[read];
            }
            ++write;
        }
    }

    tuple->length = write;
    return tuple->length;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->elements[i].type == TYPE_STRING && tuple->elements[i].data.string_value != NULL) {
            free(tuple->elements[i].data.string_value);
            tuple->elements[i].data.string_value = NULL;
        }
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->length = 0;
    tuple->capacity = 0;
}

int main(void) {
    Tuple tuple;
    tuple.length = 5;
    tuple.capacity = tuple.length;
    tuple.elements = calloc(tuple.capacity, sizeof(Element));
    if (tuple.elements == NULL) {
        return 1;
    }

    tuple.elements[0].type = TYPE_INT;
    tuple.elements[0].data.int_value = 42;

    tuple.elements[1].type = TYPE_STRING;
    tuple.elements[1].data.string_value = malloc(6);
    if (tuple.elements[1].data.string_value == NULL) {
        tuple_free(&tuple);
        return 1;
    }
    snprintf(tuple.elements[1].data.string_value, 6, "%s", "hello");

    tuple.elements[2].type = TYPE_FLOAT;
    tuple.elements[2].data.float_value = 3.14f;

    tuple.elements[3].type = TYPE_STRING;
    tuple.elements[3].data.string_value = malloc(6);
    if (tuple.elements[3].data.string_value == NULL) {
        tuple_free(&tuple);
        return 1;
    }
    snprintf(tuple.elements[3].data.string_value, 6, "%s", "world");

    tuple.elements[4].type = TYPE_INT;
    tuple.elements[4].data.int_value = 99;

    printf("Before removal:\n");
    for (size_t i = 0; i < tuple.length; ++i) {
        if (tuple.elements[i].type == TYPE_INT) {
            printf("%zu: int %d\n", i, tuple.elements[i].data.int_value);
        } else if (tuple.elements[i].type == TYPE_FLOAT) {
            printf("%zu: float %.2f\n", i, tuple.elements[i].data.float_value);
        } else if (tuple.elements[i].type == TYPE_STRING) {
            printf("%zu: string %s\n", i, tuple.elements[i].data.string_value);
        }
    }

    tuple_remove_by_type(&tuple, TYPE_STRING);

    printf("After removing strings:\n");
    for (size_t i = 0; i < tuple.length; ++i) {
        if (tuple.elements[i].type == TYPE_INT) {
            printf("%zu: int %d\n", i, tuple.elements[i].data.int_value);
        } else if (tuple.elements[i].type == TYPE_FLOAT) {
            printf("%zu: float %.2f\n", i, tuple.elements[i].data.float_value);
        } else if (tuple.elements[i].type == TYPE_STRING) {
            printf("%zu: string %s\n", i, tuple.elements[i].data.string_value);
        }
    }

    tuple_free(&tuple);
    return 0;
}