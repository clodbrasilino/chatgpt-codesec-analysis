#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)

typedef struct {
    unsigned char element;
    size_t count;
} ElementCount;

int find_most_common(const char *text, ElementCount *results, size_t max_results, size_t *num_found)
{
    size_t counts[CHARSET_SIZE];
    size_t max_count;
    size_t i;
    size_t len;
    size_t found;

    if (text == NULL || results == NULL || num_found == NULL || max_results == 0U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(text);
    if (len == 0U) {
        *num_found = 0U;
        return 0;
    }

    memset(counts, 0, sizeof(counts));

    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)text[i];
        counts[c]++;
    }

    max_count = 0U;
    for (i = 0U; i < (size_t)CHARSET_SIZE; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
        }
    }

    found = 0U;
    for (i = 0U; i < (size_t)CHARSET_SIZE; i++) {
        if (counts[i] == max_count) {
            if (found < max_results) {
                results[found].element = (unsigned char)i;
                results[found].count = counts[i];
                found++;
            } else {
                break;
            }
        }
    }

    *num_found = found;
    return 0;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog";
    ElementCount results[CHARSET_SIZE];
    size_t num_found = 0U;
    size_t i;
    int status;

    status = find_most_common(text, results, (size_t)CHARSET_SIZE, &num_found);
    if (status != 0) {
        if (fprintf(stderr, "Error: failed to analyze text\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (num_found == 0U) {
        if (printf("The text is empty\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Text: \"%s\"\n", text) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("Most common element(s) with count %zu:\n", results[0].count) < 0) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < num_found; i++) {
        if (results[i].element == (unsigned char)' ') {
            if (printf("  '(space)' : %zu\n", results[i].count) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("  '%c' : %zu\n", (int)results[i].element, results[i].count) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}