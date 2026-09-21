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
} Tuple;

size_t tuple_remove_by_type(Tuple *tuple, DataType type) {
    if (tuple == NULL || tuple->elements == NULL || tuple->length == 0) {
        return 0;
    }

    size_t write = 0;
    Element *elems = tuple->elements;
    size_t len = tuple->length;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < len; ++read) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (elems[read].type == type) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (type == TYPE_STRING && elems[read].data.string_value != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                free(elems[read].data.string_value);
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                elems[read].data.string_value = NULL;
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (write != read) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                elems[write] = elems[read];
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                if (elems[read].type == TYPE_STRING) {
                    /* Possible weaknesses found:
                     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    elems[read].data.string_value = NULL;
                }
            }
            ++write;
        }
    }

    tuple->length = write;
    return write;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }

    Element *elems = tuple->elements;
    size_t len = tuple->length;

    for (size_t i = 0; i < len; ++i) {
        if (elems[i].type == TYPE_STRING && elems[i].data.string_value != NULL) {
            free(elems[i].data.string_value);
            elems[i].data.string_value = NULL;
        }
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->length = 0;
}

int main(void) {
    Tuple tuple;
    tuple.length = 5;
    tuple.elements = calloc(tuple.length, sizeof(Element));
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