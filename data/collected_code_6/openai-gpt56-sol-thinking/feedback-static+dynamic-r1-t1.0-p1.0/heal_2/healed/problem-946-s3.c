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
    FIND_COUNT_OVERFLOW,
    FIND_ALLOCATION_FAILURE
};

int find_most_common_elements(const char *text,
                              ElementCount *results,
                              size_t capacity,
                              size_t *result_count)
{
    size_t *frequencies;
    const unsigned char *cursor;
    size_t maximum = 0;
    size_t required = 0;
    size_t index;

    if (text == NULL || results == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result_count = 0;

    frequencies = calloc(ELEMENT_CAPACITY, sizeof(*frequencies));
    if (frequencies == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    cursor = (const unsigned char *)text;

    while (*cursor != '\0') {
        index = (size_t)*cursor;

        if (index >= ELEMENT_CAPACITY) {
            free(frequencies);
            return FIND_INVALID_ARGUMENT;
        }

        if (frequencies[index] == SIZE_MAX) {
            free(frequencies);
            return FIND_COUNT_OVERFLOW;
        }

        ++frequencies[index];

        if (frequencies[index] > maximum) {
            maximum = frequencies[index];
        }

        ++cursor;
    }

    if (maximum == 0) {
        free(frequencies);
        return FIND_SUCCESS;
    }

    for (index = 0; index < ELEMENT_CAPACITY; ++index) {
        if (frequencies[index] == maximum) {
            ++required;
        }
    }

    if (capacity < required) {
        free(frequencies);
        return FIND_INSUFFICIENT_CAPACITY;
    }

    for (index = 0; index < ELEMENT_CAPACITY; ++index) {
        if (frequencies[index] == maximum) {
            results[*result_count].element = (unsigned char)index;
            results[*result_count].count = maximum;
            ++*result_count;
        }
    }

    free(frequencies);
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

int main(int argc, char *argv[])
{
    ElementCount *results;
    const char *program_name;
    const char *text;
    size_t result_count = 0;
    size_t index;
    int status;
    int exit_status = EXIT_FAILURE;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (ELEMENT_CAPACITY > SIZE_MAX / sizeof(*results)) {
        if (fprintf(stderr, "Unable to allocate result storage.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    results = calloc(ELEMENT_CAPACITY, sizeof(*results));
    if (results == NULL) {
        if (fprintf(stderr, "Unable to allocate result storage.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    text = argv[1];

    status = find_most_common_elements(
        text,
        results,
        ELEMENT_CAPACITY,
        &result_count
    );

    if (status != FIND_SUCCESS) {
        if (fprintf(stderr, "Unable to process the specified text.\n") < 0) {
            free(results);
            return EXIT_FAILURE;
        }
        free(results);
        return EXIT_FAILURE;
    }

    if (result_count == 0) {
        if (printf("The specified text is empty.\n") < 0) {
            free(results);
            return EXIT_FAILURE;
        }

        free(results);
        return EXIT_SUCCESS;
    }

    for (index = 0; index < result_count; ++index) {
        if (print_element(results[index].element) < 0) {
            free(results);
            return EXIT_FAILURE;
        }

        if (printf(": %zu\n", results[index].count) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    exit_status = EXIT_SUCCESS;
    free(results);
    return exit_status;
}