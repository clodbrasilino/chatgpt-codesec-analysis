#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ELEMENT_CAPACITY ((size_t)UCHAR_MAX + 1U)

typedef struct {
    unsigned char element;
    size_t count;
} ElementCount;

enum FindStatus {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_INSUFFICIENT_CAPACITY,
    FIND_COUNT_OVERFLOW
};

int find_most_common_elements(const char *text,
                              ElementCount *results,
                              size_t capacity,
                              size_t *result_count)
{
    size_t frequencies[ELEMENT_CAPACITY] = {0};
    const unsigned char *cursor;
    size_t maximum = 0;
    size_t required = 0;
    size_t index;

    if (text == NULL || results == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result_count = 0;
    cursor = (const unsigned char *)text;

    while (*cursor != '\0') {
        if (frequencies[*cursor] == SIZE_MAX) {
            return FIND_COUNT_OVERFLOW;
        }

        ++frequencies[*cursor];

        if (frequencies[*cursor] > maximum) {
            maximum = frequencies[*cursor];
        }

        ++cursor;
    }

    if (maximum == 0) {
        return FIND_SUCCESS;
    }

    for (index = 0; index < ELEMENT_CAPACITY; ++index) {
        if (frequencies[index] == maximum) {
            ++required;
        }
    }

    if (capacity < required) {
        return FIND_INSUFFICIENT_CAPACITY;
    }

    for (index = 0; index < ELEMENT_CAPACITY; ++index) {
        if (frequencies[index] == maximum) {
            results[*result_count].element = (unsigned char)index;
            results[*result_count].count = maximum;
            ++*result_count;
        }
    }

    return FIND_SUCCESS;
}

static int print_element(unsigned char element)
{
    switch (element) {
        case '\n':
            return printf("'\\n'");
        case '\r':
            return printf("'\\r'");
        case '\t':
            return printf("'\\t'");
        case '\\':
            return printf("'\\\\'");
        case '\'':
            return printf("'\\''");
        default:
            if (isprint((int)element) != 0) {
                return printf("'%c'", (int)element);
            }
            return printf("0x%02X", (unsigned int)element);
    }
}

int main(int argc, char * const argv[])
{
    ElementCount results[ELEMENT_CAPACITY];
    size_t result_count = 0;
    size_t index;
    int status;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    status = find_most_common_elements(argv[1],
                                       results,
                                       ELEMENT_CAPACITY,
                                       &result_count);

    if (status != FIND_SUCCESS) {
        if (fprintf(stderr, "Unable to process the specified text.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (result_count == 0) {
        if (printf("The specified text is empty.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    for (index = 0; index < result_count; ++index) {
        if (print_element(results[index].element) < 0) {
            return EXIT_FAILURE;
        }

        if (printf(": %zu\n", results[index].count) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}