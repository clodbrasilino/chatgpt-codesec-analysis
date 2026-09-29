#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char element;
    size_t count;
} ElementCount;

typedef enum {
    FIND_OK,
    FIND_INVALID_ARGUMENT,
    FIND_OUT_OF_MEMORY,
    FIND_SIZE_OVERFLOW
} FindStatus;

FindStatus find_most_common_elements(const char *text,
                                     ElementCount **results,
                                     size_t *result_count)
{
    size_t *frequencies;
    size_t alphabet_size;
    size_t maximum = 0;
    size_t matches = 0;
    size_t index = 0;
    const unsigned char *current;

    if (results == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *results = NULL;
    *result_count = 0;

    if (text == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return FIND_SIZE_OVERFLOW;
    }

    alphabet_size = (size_t)UCHAR_MAX + 1U;

    if (alphabet_size > SIZE_MAX / sizeof(*frequencies)) {
        return FIND_SIZE_OVERFLOW;
    }

    frequencies = calloc(alphabet_size, sizeof(*frequencies));
    if (frequencies == NULL) {
        return FIND_OUT_OF_MEMORY;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        ++frequencies[*current];

        if (frequencies[*current] > maximum) {
            maximum = frequencies[*current];
        }

        ++current;
    }

    if (maximum == 0) {
        free(frequencies);
        return FIND_OK;
    }

    for (size_t i = 0; i < alphabet_size; ++i) {
        if (frequencies[i] == maximum) {
            ++matches;
        }
    }

    if (matches > SIZE_MAX / sizeof(**results)) {
        free(frequencies);
        return FIND_SIZE_OVERFLOW;
    }

    *results = malloc(matches * sizeof(**results));
    if (*results == NULL) {
        free(frequencies);
        return FIND_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < alphabet_size; ++i) {
        if (frequencies[i] == maximum) {
            (*results)[index].element = (unsigned char)i;
            (*results)[index].count = maximum;
            ++index;
        }
    }

    *result_count = matches;
    free(frequencies);

    return FIND_OK;
}

static int print_element(const ElementCount *result)
{
    int status;

    if (result == NULL) {
        return -1;
    }

    switch (result->element) {
        case '\n':
            status = printf("\\n: %zu\n", result->count);
            break;
        case '\r':
            status = printf("\\r: %zu\n", result->count);
            break;
        case '\t':
            status = printf("\\t: %zu\n", result->count);
            break;
        case '\\':
            status = printf("'\\\\': %zu\n", result->count);
            break;
        case '\'':
            status = printf("'\\'': %zu\n", result->count);
            break;
        default:
            if (isprint((int)result->element)) {
                status = printf("'%c': %zu\n",
                                (int)result->element,
                                result->count);
            } else {
                status = printf("0x%02X: %zu\n",
                                (unsigned int)result->element,
                                result->count);
            }
            break;
    }

    return status < 0 ? -1 : 0;
}

int main(int argc, char * const argv[])
{
    ElementCount *results = NULL;
    size_t result_count = 0;
    FindStatus status;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    status = find_most_common_elements(argv[1], &results, &result_count);

    if (status != FIND_OK) {
        const char *message;

        switch (status) {
            case FIND_INVALID_ARGUMENT:
                message = "Invalid argument";
                break;
            case FIND_OUT_OF_MEMORY:
                message = "Out of memory";
                break;
            case FIND_SIZE_OVERFLOW:
                message = "Size overflow";
                break;
            default:
                message = "Unknown error";
                break;
        }

        if (fprintf(stderr, "%s\n", message) < 0) {
            free(results);
            return EXIT_FAILURE;
        }

        free(results);
        return EXIT_FAILURE;
    }

    if (result_count == 0) {
        if (printf("The text is empty.\n") < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    } else {
        for (size_t i = 0; i < result_count; ++i) {
            if (print_element(&results[i]) != 0) {
                free(results);
                return EXIT_FAILURE;
            }
        }
    }

    free(results);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}