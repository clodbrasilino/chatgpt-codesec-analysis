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

static char *duplicate_string(const char *source, size_t source_length)
{
    char *copy;

    if (source == NULL || source_length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (source_length > 0U) {
        memcpy(copy, source, source_length);
    }
    copy[source_length] = '\0';

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
    size_t write_index = 0U;

    if (tuple == NULL ||
        (tuple->size > 0U && tuple->elements == NULL)) {
        return -1;
    }

    for (size_t read_index = 0U; read_index < tuple->size; ++read_index) {
        if (tuple->elements[read_index].type == type) {
            destroy_element(&tuple->elements[read_index]);
            continue;
        }

        if (write_index != read_index) {
            tuple->elements[write_index] = tuple->elements[read_index];
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
        Element *resized = realloc(
            tuple->elements,
            write_index * sizeof(*tuple->elements)
        );

        if (resized != NULL) {
            tuple->elements = resized;
        }
    }

    return 0;
}

static void print_tuple(const Tuple *tuple)
{
    if (tuple == NULL ||
        (tuple->size > 0U && tuple->elements == NULL)) {
        return;
    }

    putchar('(');

    for (size_t i = 0U; i < tuple->size; ++i) {
        if (i > 0U) {
            fputs(", ", stdout);
        }

        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", tuple->elements[i].value.integer);
                break;

            case TYPE_DOUBLE:
                printf("%g", tuple->elements[i].value.real);
                break;

            case TYPE_STRING:
                if (tuple->elements[i].value.string != NULL) {
                    putchar('"');
                    fputs(tuple->elements[i].value.string, stdout);
                    putchar('"');
                } else {
                    fputs("<null>", stdout);
                }
                break;

            default:
                fputs("<invalid>", stdout);
                break;
        }
    }

    fputs(")\n", stdout);
}

int main(void)
{
    Tuple tuple = {NULL, 0U};
    const size_t count = 5U;
    size_t initialized = 0U;
    static const char alpha[] = "alpha";
    static const char beta[] = "beta";

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
        duplicate_string(alpha, sizeof(alpha) - 1U);
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
        duplicate_string(beta, sizeof(beta) - 1U);
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