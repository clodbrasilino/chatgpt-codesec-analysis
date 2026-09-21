#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ELEMENT_INT,
    ELEMENT_DOUBLE,
    ELEMENT_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        int64_t integer;
        double real;
        char *string;
    } value;
} Element;

typedef struct {
    Element *elements;
    size_t length;
} Tuple;

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
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

    if (element->type == ELEMENT_STRING) {
        free(element->value.string);
        element->value.string = NULL;
    }
}

static void destroy_tuple(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (i = 0U; i < tuple->length; ++i) {
            destroy_element(&tuple->elements[i]);
        }
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->length = 0U;
}

static int remove_type(Tuple *tuple, ElementType type)
{
    size_t read_index;
    size_t write_index = 0U;

    if (tuple == NULL ||
        (tuple->length != 0U && tuple->elements == NULL)) {
        return -1;
    }

    for (read_index = 0U; read_index < tuple->length; ++read_index) {
        if (tuple->elements[read_index].type == type) {
            destroy_element(&tuple->elements[read_index]);
            continue;
        }

        if (write_index != read_index) {
            tuple->elements[write_index] = tuple->elements[read_index];
            memset(&tuple->elements[read_index], 0,
                   sizeof(tuple->elements[read_index]));
        }

        ++write_index;
    }

    tuple->length = write_index;

    if (write_index == 0U) {
        free(tuple->elements);
        tuple->elements = NULL;
    }

    return 0;
}

static int print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL ||
        (tuple->length != 0U && tuple->elements == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (i = 0U; i < tuple->length; ++i) {
        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        switch (tuple->elements[i].type) {
            case ELEMENT_INT:
                if (printf("%" PRId64,
                           tuple->elements[i].value.integer) < 0) {
                    return -1;
                }
                break;

            case ELEMENT_DOUBLE:
                if (printf("%g", tuple->elements[i].value.real) < 0) {
                    return -1;
                }
                break;

            case ELEMENT_STRING:
                if (tuple->elements[i].value.string == NULL ||
                    printf("\"%s\"",
                           tuple->elements[i].value.string) < 0) {
                    return -1;
                }
                break;

            default:
                return -1;
        }
    }

    if (puts(")") == EOF) {
        return -1;
    }

    return ferror(stdout) ? -1 : 0;
}

int main(void)
{
    static const char alpha[] = "alpha";
    static const char beta[] = "beta";
    Tuple tuple = { NULL, 0U };
    int status = EXIT_FAILURE;

    if (5U > SIZE_MAX / sizeof(*tuple.elements)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements = calloc(5U, sizeof(*tuple.elements));
    if (tuple.elements == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.length = 5U;

    tuple.elements[0].type = ELEMENT_INT;
    tuple.elements[0].value.integer = INT64_C(42);

    tuple.elements[1].type = ELEMENT_STRING;
    tuple.elements[1].value.string =
        duplicate_string(alpha, sizeof(alpha));
    if (tuple.elements[1].value.string == NULL) {
        fputs("String allocation failed\n", stderr);
        goto cleanup;
    }

    tuple.elements[2].type = ELEMENT_DOUBLE;
    tuple.elements[2].value.real = 3.14;

    tuple.elements[3].type = ELEMENT_STRING;
    tuple.elements[3].value.string =
        duplicate_string(beta, sizeof(beta));
    if (tuple.elements[3].value.string == NULL) {
        fputs("String allocation failed\n", stderr);
        goto cleanup;
    }

    tuple.elements[4].type = ELEMENT_INT;
    tuple.elements[4].value.integer = INT64_C(7);

    if (remove_type(&tuple, ELEMENT_STRING) != 0) {
        fputs("Unable to remove elements\n", stderr);
        goto cleanup;
    }

    if (print_tuple(&tuple) != 0) {
        fputs("Unable to print tuple\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    destroy_tuple(&tuple);
    return status;
}