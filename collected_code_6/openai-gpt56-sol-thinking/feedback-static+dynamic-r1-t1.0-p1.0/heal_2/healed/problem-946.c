#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char element;
    size_t count;
} CommonElement;

static int find_most_common_elements(const char *text,
                                     CommonElement *results,
                                     size_t capacity,
                                     size_t *result_count)
{
    size_t counts[(size_t)UCHAR_MAX + 1U] = {0};
    size_t maximum = 0;
    size_t needed = 0;
    size_t i;

    if (text == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    *result_count = 0;

    while (*text != '\0') {
        unsigned char element = (unsigned char)*text;

        if (counts[element] == SIZE_MAX) {
            return -1;
        }

        counts[element]++;

        if (counts[element] > maximum) {
            maximum = counts[element];
        }

        text++;
    }

    if (maximum == 0) {
        return 0;
    }

    for (i = 0; i < (size_t)UCHAR_MAX + 1U; i++) {
        if (counts[i] == maximum) {
            needed++;
        }
    }

    if (needed > capacity) {
        return -1;
    }

    for (i = 0; i < (size_t)UCHAR_MAX + 1U; i++) {
        if (counts[i] == maximum) {
            results[*result_count].element = (unsigned char)i;
            results[*result_count].count = counts[i];
            (*result_count)++;
        }
    }

    return 0;
}

static int print_common_element(const CommonElement *result)
{
    unsigned char element;

    if (result == NULL) {
        return -1;
    }

    element = result->element;

    switch (element) {
        case '\n':
            return printf("'\\n': %zu\n", result->count) < 0 ? -1 : 0;
        case '\r':
            return printf("'\\r': %zu\n", result->count) < 0 ? -1 : 0;
        case '\t':
            return printf("'\\t': %zu\n", result->count) < 0 ? -1 : 0;
        case '\\':
            return printf("'\\\\': %zu\n", result->count) < 0 ? -1 : 0;
        case '\'':
            return printf("'\\'': %zu\n", result->count) < 0 ? -1 : 0;
        default:
            if (isprint((int)element)) {
                return printf("'%c': %zu\n", (int)element,
                              result->count) < 0 ? -1 : 0;
            }

            return printf("0x%02X: %zu\n", (unsigned int)element,
                          result->count) < 0 ? -1 : 0;
    }
}

int main(int argc, char *const argv[])
{
    CommonElement results[(size_t)UCHAR_MAX + 1U];
    size_t result_count;
    size_t i;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s \"text\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (find_most_common_elements(argv[1], results,
                                  (size_t)UCHAR_MAX + 1U,
                                  &result_count) != 0) {
        if (fputs("Unable to process the specified text.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (result_count == 0) {
        if (puts("The specified text is empty.") == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    for (i = 0; i < result_count; i++) {
        if (print_common_element(&results[i]) != 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}