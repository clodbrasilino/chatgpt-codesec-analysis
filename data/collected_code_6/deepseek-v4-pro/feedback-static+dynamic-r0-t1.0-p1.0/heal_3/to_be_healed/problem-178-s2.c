#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* Possible weaknesses found:
 *  'ptrdiff_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
 */
#include <stdint.h>

typedef struct {
    char *literal;
    size_t position;
    bool found;
} SearchResult;

SearchResult *search_literals(const char *text, const char **literals, size_t literal_count) {
    if (text == NULL || literals == NULL || literal_count == 0) {
        return NULL;
    }

    SearchResult *results = (SearchResult *)calloc(literal_count, sizeof(SearchResult));
    if (results == NULL) {
        return NULL;
    }

    size_t text_len = strnlen(text, SIZE_MAX);
    if (text_len == SIZE_MAX) {
        free(results);
        return NULL;
    }

    for (size_t i = 0; i < literal_count; i++) {
        if (literals[i] == NULL) {
            free(results);
            return NULL;
        }

        size_t literal_len = strnlen(literals[i], SIZE_MAX);
        if (literal_len == SIZE_MAX) {
            free(results);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        results[i].literal = (char *)literals[i];

        if (literal_len == 0 || literal_len > text_len) {
            results[i].found = false;
            results[i].position = 0;
            continue;
        }

        const char *pos = strstr(text, literals[i]);
        if (pos != NULL) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'ptrdiff_t'
             *  unknown type name 'ptrdiff_t'
             */
            ptrdiff_t diff = pos - text;
            /* Possible weaknesses found:
             *  use of undeclared identifier 'diff'
             */
            if (diff < 0 || (size_t)diff > text_len - literal_len) {
                results[i].found = false;
                results[i].position = 0;
            } else {
                results[i].found = true;
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'diff'
                 */
                results[i].position = (size_t)diff;
            }
        } else {
            results[i].found = false;
            results[i].position = 0;
        }
    }

    return results;
}

void print_results(const SearchResult *results, size_t count) {
    if (results == NULL) {
        printf("No results to display\n");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (results[i].found) {
            printf("'%s' found at position %zu\n", results[i].literal, results[i].position);
        } else {
            printf("'%s' not found\n", results[i].literal);
        }
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {
        "quick",
        "fox",
        "cat",
        "lazy",
        "dog"
    };
    size_t literal_count = sizeof(literals) / sizeof(literals[0]);

    SearchResult *results = search_literals(text, literals, literal_count);
    if (results == NULL) {
        fprintf(stderr, "Error searching literals\n");
        return EXIT_FAILURE;
    }

    print_results(results, literal_count);
    free(results);
    return EXIT_SUCCESS;
}