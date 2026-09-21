#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 8U
#define MAX_STRING_LENGTH 4096U

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        double d;
        char c;
        char *s;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
    size_t capacity;
} Tuple;

static void free_element(TupleElement *element)
{
    if (element != NULL && element->type == TYPE_STRING && element->value.s != NULL) {
        free(element->value.s);
        element->value.s = NULL;
    }
}

Tuple *tuple_create(void)
{
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));

    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = (TupleElement *)malloc(INITIAL_CAPACITY * sizeof(TupleElement));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->count = 0U;
    tuple->capacity = INITIAL_CAPACITY;

    return tuple;
}

static int tuple_reserve(Tuple *tuple, size_t needed)
{
    TupleElement *new_elements;
    size_t new_capacity;

    if (tuple->capacity >= needed) {
        return 0;
    }

    if (tuple->capacity > SIZE_MAX / 2U) {
        new_capacity = needed;
    } else {
        new_capacity = tuple->capacity * 2U;
    }

    if (new_capacity < needed) {
        new_capacity = needed;
    }

    if (new_capacity > SIZE_MAX / sizeof(TupleElement)) {
        return -1;
    }

    new_elements = (TupleElement *)realloc(tuple->elements, new_capacity * sizeof(TupleElement));
    if (new_elements == NULL) {
        return -1;
    }

    tuple->elements = new_elements;
    tuple->capacity = new_capacity;

    return 0;
}

int tuple_add_int(Tuple *tuple, int value)
{
    if (tuple == NULL) {
        return -1;
    }
    if (tuple_reserve(tuple, tuple->count + 1U) != 0) {
        return -1;
    }
    tuple->elements[tuple->count].type = TYPE_INT;
    tuple->elements[tuple->count].value.i = value;
    tuple->count++;
    return 0;
}

int tuple_add_float(Tuple *tuple, float value)
{
    if (tuple == NULL) {
        return -1;
    }
    if (tuple_reserve(tuple, tuple->count + 1U) != 0) {
        return -1;
    }
    tuple->elements[tuple->count].type = TYPE_FLOAT;
    tuple->elements[tuple->count].value.f = value;
    tuple->count++;
    return 0;
}

int tuple_add_double(Tuple *tuple, double value)
{
    if (tuple == NULL) {
        return -1;
    }
    if (tuple_reserve(tuple, tuple->count + 1U) != 0) {
        return -1;
    }
    tuple->elements[tuple->count].type = TYPE_DOUBLE;
    tuple->elements[tuple->count].value.d = value;
    tuple->count++;
    return 0;
}

int tuple_add_char(Tuple *tuple, char value)
{
    if (tuple == NULL) {
        return -1;
    }
    if (tuple_reserve(tuple, tuple->count + 1U) != 0) {
        return -1;
    }
    tuple->elements[tuple->count].type = TYPE_CHAR;
    tuple->elements[tuple->count].value.c = value;
    tuple->count++;
    return 0;
}

int tuple_add_string(Tuple *tuple, const char *value)
{
    char *copy;
    size_t len;
    int written;

    if (tuple == NULL || value == NULL) {
        return -1;
    }
    if (tuple_reserve(tuple, tuple->count + 1U) != 0) {
        return -1;
    }

    len = strnlen(value, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return -1;
    }

    copy = (char *)malloc(len + 1U);
    if (copy == NULL) {
        return -1;
    }

    written = snprintf(copy, len + 1U, "%s", value);
    if (written < 0 || (size_t)written != len) {
        free(copy);
        return -1;
    }

    tuple->elements[tuple->count].type = TYPE_STRING;
    tuple->elements[tuple->count].value.s = copy;
    tuple->count++;

    return 0;
}

size_t tuple_remove_by_type(Tuple *tuple, DataType type_to_remove)
{
    size_t read_index;
    size_t write_index;
    size_t removed;

    if (tuple == NULL || tuple->elements == NULL) {
        return 0U;
    }

    write_index = 0U;
    removed = 0U;

    for (read_index = 0U; read_index < tuple->count; read_index++) {
        if (tuple->elements[read_index].type == type_to_remove) {
            free_element(&tuple->elements[read_index]);
            removed++;
        } else {
            if (write_index != read_index) {
                tuple->elements[write_index] = tuple->elements[read_index];
            }
            write_index++;
        }
    }

    tuple->count = write_index;

    return removed;
}

void tuple_print(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        printf("(null)\n");
        return;
    }

    printf("(");
    for (i = 0U; i < tuple->count; i++) {
        if (i > 0U) {
            printf(", ");
        }
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", tuple->elements[i].value.i);
                break;
            case TYPE_FLOAT:
                printf("%f", (double)tuple->elements[i].value.f);
                break;
            case TYPE_DOUBLE:
                printf("%f", tuple->elements[i].value.d);
                break;
            case TYPE_CHAR:
                printf("'%c'", tuple->elements[i].value.c);
                break;
            case TYPE_STRING:
                printf("\"%s\"", tuple->elements[i].value.s != NULL
                                 ? tuple->elements[i].value.s : "(null)");
                break;
            default:
                printf("<unknown>");
                break;
        }
    }
    printf(")\n");
}

void tuple_destroy(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0U; i < tuple->count; i++) {
        free_element(&tuple->elements[i]);
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->count = 0U;
    tuple->capacity = 0U;

    free(tuple);
}

int main(void)
{
    Tuple *tuple;
    size_t removed;
    int status;

    tuple = tuple_create();
    if (tuple == NULL) {
        fprintf(stderr, "Error: failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    status = 0;
    status |= tuple_add_int(tuple, 10);
    status |= tuple_add_float(tuple, 2.5f);
    status |= tuple_add_string(tuple, "hello");
    status |= tuple_add_int(tuple, 20);
    status |= tuple_add_double(tuple, 3.14159);
    status |= tuple_add_string(tuple, "world");
    status |= tuple_add_char(tuple, 'A');
    status |= tuple_add_int(tuple, 30);

    if (status != 0) {
        fprintf(stderr, "Error: failed to add element to tuple.\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    tuple_print(tuple);

    removed = tuple_remove_by_type(tuple, TYPE_INT);
    printf("Removed %zu int element(s): ", removed);
    tuple_print(tuple);

    removed = tuple_remove_by_type(tuple, TYPE_STRING);
    printf("Removed %zu string element(s): ", removed);
    tuple_print(tuple);

    tuple_destroy(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}