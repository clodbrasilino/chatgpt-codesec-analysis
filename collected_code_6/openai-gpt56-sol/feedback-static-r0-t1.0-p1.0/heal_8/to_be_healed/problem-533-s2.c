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

static char *duplicate_string(const char *source, size_t source_size)
{
    if (source == NULL || source_size == 0) {
        return NULL;
    }

    const char *terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    size_t length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    size_t destination_size = length + 1;
    char *copy = malloc(destination_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
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
    }

    memset(element, 0, sizeof(*element));
}

static void destroy_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (size_t i = 0; i < tuple->size; ++i) {
            destroy_element(&tuple->elements[i]);
        }
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
}

static int tuple_is_valid(const Tuple *tuple)
{
    if (tuple == NULL) {
        return 0;
    }

    if (tuple->size == 0) {
        return tuple->elements == NULL;
    }

    return tuple->elements != NULL &&
           tuple->size <= SIZE_MAX / sizeof(*tuple->elements);
}

static int remove_type(Tuple *tuple, DataType type)
{
    if (!tuple_is_valid(tuple)) {
        return -1;
    }

    size_t write_index = 0;

    for (size_t read_index = 0; read_index < tuple->size; ++read_index) {
        Element *source = &tuple->elements[read_index];

        if (source->type == type) {
            destroy_element(source);
            continue;
        }

        if (write_index != read_index) {
            tuple->elements[write_index] = *source;
            memset(source, 0, sizeof(*source));
        }

        ++write_index;
    }

    if (write_index == 0) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
        return 0;
    }

    tuple->size = write_index;

    size_t allocation_size = write_index * sizeof(*tuple->elements);
    Element *resized = realloc(tuple->elements, allocation_size);
    if (resized != NULL) {
        tuple->elements = resized;
    }

    return 0;
}

static void print_tuple(const Tuple *tuple)
{
    if (!tuple_is_valid(tuple)) {
        return;
    }

    putchar('(');

    for (size_t i = 0; i < tuple->size; ++i) {
        if (i != 0) {
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
                    printf("\"%s\"", tuple->elements[i].value.string);
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
    static const char alpha[] = "alpha";
    static const char beta[] = "beta";
    const size_t element_count = 5;
    Tuple tuple = {NULL, 0};

    if (element_count > SIZE_MAX / sizeof(*tuple.elements)) {
        fputs("Tuple size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements = calloc(element_count, sizeof(*tuple.elements));
    if (tuple.elements == NULL) {
        fputs("Failed to allocate tuple\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.size = element_count;

    tuple.elements[0].type = TYPE_INT;
    tuple.elements[0].value.integer = 10;

    tuple.elements[1].type = TYPE_STRING;
    tuple.elements[1].value.string = duplicate_string(alpha, sizeof(alpha));
    if (tuple.elements[1].value.string == NULL) {
        destroy_tuple(&tuple);
        fputs("Failed to allocate string\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements[2].type = TYPE_DOUBLE;
    tuple.elements[2].value.real = 3.14;

    tuple.elements[3].type = TYPE_STRING;
    tuple.elements[3].value.string = duplicate_string(beta, sizeof(beta));
    if (tuple.elements[3].value.string == NULL) {
        destroy_tuple(&tuple);
        fputs("Failed to allocate string\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements[4].type = TYPE_INT;
    tuple.elements[4].value.integer = 20;

    if (remove_type(&tuple, TYPE_STRING) != 0) {
        destroy_tuple(&tuple);
        fputs("Failed to remove elements\n", stderr);
        return EXIT_FAILURE;
    }

    print_tuple(&tuple);
    destroy_tuple(&tuple);

    return EXIT_SUCCESS;
}