#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int integer;
        double real;
        char *string;
    } value;
} Element;

typedef struct {
    Element *elements;
    size_t size;
} Tuple;

static char *duplicate_string(const char *source, size_t length)
{
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t source_length = strlen(source);
    if (source_length != length) {
        return NULL;
    }

    size_t allocation_size = length + 1U;
    char *copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void destroy_element(Element *element)
{
    if (element == NULL) {
        return;
    }

    if (element->type == TYPE_STRING) {
        free(element->value.string);
        element->value.string = NULL;
    }
}

static void destroy_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (size_t i = 0U; i < tuple->size; ++i) {
            destroy_element(&tuple->elements[i]);
        }
        free(tuple->elements);
    }

    tuple->elements = NULL;
    tuple->size = 0U;
}

static int remove_type(Tuple *tuple, DataType type)
{
    if (tuple == NULL ||
        (tuple->size != 0U && tuple->elements == NULL)) {
        return -1;
    }

    size_t write_index = 0U;

    for (size_t read_index = 0U; read_index < tuple->size; ++read_index) {
        Element *element = &tuple->elements[read_index];

        if (element->type == type) {
            destroy_element(element);
            continue;
        }

        if (write_index != read_index) {
            tuple->elements[write_index] = *element;
            memset(element, 0, sizeof(*element));
        }

        ++write_index;
    }

    if (write_index == 0U) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0U;
        return 0;
    }

    tuple->size = write_index;

    if (write_index <= SIZE_MAX / sizeof(*tuple->elements)) {
        size_t new_size = write_index * sizeof(*tuple->elements);
        Element *resized = realloc(tuple->elements, new_size);

        if (resized != NULL) {
            tuple->elements = resized;
        }
    }

    return 0;
}

static void print_tuple(const Tuple *tuple)
{
    if (tuple == NULL ||
        (tuple->size != 0U && tuple->elements == NULL)) {
        return;
    }

    putchar('(');

    for (size_t i = 0U; i < tuple->size; ++i) {
        if (i != 0U) {
            fputs(", ", stdout);
        }

        const Element *element = &tuple->elements[i];

        switch (element->type) {
            case TYPE_INT:
                printf("%d", element->value.integer);
                break;
            case TYPE_DOUBLE:
                printf("%g", element->value.real);
                break;
            case TYPE_STRING:
                if (element->value.string != NULL) {
                    printf("\"%s\"", element->value.string);
                } else {
                    fputs("<null>", stdout);
                }
                break;
            default:
                fputs("<invalid>", stdout);
                break;
        }
    }

    puts(")");
}

int main(void)
{
    const size_t count = 5U;
    Tuple tuple = {NULL, 0U};
    size_t initialized = 0U;

    if (count > SIZE_MAX / sizeof(*tuple.elements)) {
        fputs("Tuple size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements = calloc(count, sizeof(*tuple.elements));
    if (tuple.elements == NULL) {
        fputs("Failed to allocate tuple\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements[0].type = TYPE_INT;
    tuple.elements[0].value.integer = 42;
    ++initialized;

    tuple.elements[1].type = TYPE_STRING;
    tuple.elements[1].value.string =
        duplicate_string("alpha", sizeof("alpha") - 1U);
    if (tuple.elements[1].value.string == NULL) {
        tuple.size = initialized;
        destroy_tuple(&tuple);
        fputs("Failed to allocate string\n", stderr);
        return EXIT_FAILURE;
    }
    ++initialized;

    tuple.elements[2].type = TYPE_DOUBLE;
    tuple.elements[2].value.real = 3.14;
    ++initialized;

    tuple.elements[3].type = TYPE_STRING;
    tuple.elements[3].value.string =
        duplicate_string("beta", sizeof("beta") - 1U);
    if (tuple.elements[3].value.string == NULL) {
        tuple.size = initialized;
        destroy_tuple(&tuple);
        fputs("Failed to allocate string\n", stderr);
        return EXIT_FAILURE;
    }
    ++initialized;

    tuple.elements[4].type = TYPE_INT;
    tuple.elements[4].value.integer = 7;
    ++initialized;

    tuple.size = initialized;

    print_tuple(&tuple);

    if (remove_type(&tuple, TYPE_STRING) != 0) {
        destroy_tuple(&tuple);
        fputs("Failed to remove elements\n", stderr);
        return EXIT_FAILURE;
    }

    print_tuple(&tuple);
    destroy_tuple(&tuple);

    return EXIT_SUCCESS;
}