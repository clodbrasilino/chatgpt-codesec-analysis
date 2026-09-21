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

    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
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
    }

    memset(element, 0, sizeof(*element));
}

static void destroy_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (size_t i = 0U; i < tuple->length; ++i) {
            destroy_element(&tuple->elements[i]);
        }

        free(tuple->elements);
    }

    tuple->elements = NULL;
    tuple->length = 0U;
}

static int remove_type(Tuple *tuple, ElementType type)
{
    size_t write_index = 0U;

    if (tuple == NULL ||
        (tuple->length != 0U && tuple->elements == NULL)) {
        return -1;
    }

    for (size_t read_index = 0U; read_index < tuple->length; ++read_index) {
        Element *current = &tuple->elements[read_index];

        if (current->type == type) {
            destroy_element(current);
            continue;
        }

        if (write_index != read_index) {
            tuple->elements[write_index] = *current;
            memset(current, 0, sizeof(*current));
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

static int print_quoted_string(const char *string)
{
    const unsigned char *cursor;

    if (string == NULL || fputc('"', stdout) == EOF) {
        return -1;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        switch (*cursor) {
        case '"':
            if (fputs("\\\"", stdout) == EOF) {
                return -1;
            }
            break;

        case '\\':
            if (fputs("\\\\", stdout) == EOF) {
                return -1;
            }
            break;

        case '\n':
            if (fputs("\\n", stdout) == EOF) {
                return -1;
            }
            break;

        case '\r':
            if (fputs("\\r", stdout) == EOF) {
                return -1;
            }
            break;

        case '\t':
            if (fputs("\\t", stdout) == EOF) {
                return -1;
            }
            break;

        default:
            if (*cursor < 0x20U || *cursor == 0x7FU) {
                if (fprintf(stdout, "\\x%02X", (unsigned int)*cursor) < 0) {
                    return -1;
                }
            } else if (fputc((int)*cursor, stdout) == EOF) {
                return -1;
            }
            break;
        }

        ++cursor;
    }

    return fputc('"', stdout) == EOF ? -1 : 0;
}

static int print_tuple(const Tuple *tuple)
{
    if (tuple == NULL ||
        (tuple->length != 0U && tuple->elements == NULL)) {
        return -1;
    }

    if (fputc('(', stdout) == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < tuple->length; ++i) {
        const Element *element = &tuple->elements[i];

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        switch (element->type) {
        case ELEMENT_INT:
            if (fprintf(stdout, "%" PRId64, element->value.integer) < 0) {
                return -1;
            }
            break;

        case ELEMENT_DOUBLE:
            if (fprintf(stdout, "%g", element->value.real) < 0) {
                return -1;
            }
            break;

        case ELEMENT_STRING:
            if (print_quoted_string(element->value.string) != 0) {
                return -1;
            }
            break;

        default:
            return -1;
        }
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return ferror(stdout) != 0 ? -1 : 0;
}

int main(void)
{
    static const char alpha[] = "alpha";
    static const char beta[] = "beta";
    const size_t element_count = 5U;
    Tuple tuple = {NULL, 0U};
    int status = EXIT_FAILURE;

    if (element_count > SIZE_MAX / sizeof(*tuple.elements)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.elements = calloc(element_count, sizeof(*tuple.elements));
    if (tuple.elements == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.length = element_count;

    tuple.elements[0].type = ELEMENT_INT;
    tuple.elements[0].value.integer = INT64_C(42);

    tuple.elements[1].type = ELEMENT_STRING;
    tuple.elements[1].value.string = duplicate_string(alpha, sizeof(alpha));
    if (tuple.elements[1].value.string == NULL) {
        fputs("String allocation failed\n", stderr);
        goto cleanup;
    }

    tuple.elements[2].type = ELEMENT_DOUBLE;
    tuple.elements[2].value.real = 3.14;

    tuple.elements[3].type = ELEMENT_STRING;
    tuple.elements[3].value.string = duplicate_string(beta, sizeof(beta));
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