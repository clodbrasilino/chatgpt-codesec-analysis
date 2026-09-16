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
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t maximum = 0;
    size_t needed = 0;
    size_t i;

    if (text == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    *result_count = 0;

    while (*text != '\0') {
        const unsigned char element = (unsigned char)*text;

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

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] == maximum) {
            needed++;
        }
    }

    if (needed > capacity) {
        return -1;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    CommonElement results[UCHAR_MAX + 1];
    size_t result_count;
    size_t i;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s \"text\"\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (find_most_common_elements(argv[1], results, UCHAR_MAX + 1,
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