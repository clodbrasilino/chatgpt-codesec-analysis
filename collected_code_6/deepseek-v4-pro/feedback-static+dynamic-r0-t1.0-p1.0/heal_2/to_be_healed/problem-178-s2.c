#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *literal;
    size_t position;
    bool found;
} SearchResult;

SearchResult *search_literals(const char *text, const char **literals, size_t literal_count) {
    if (text == NULL || literals == NULL || literal_count == 0) {
        return NULL;
    }

    SearchResult *results = (SearchResult *)malloc(literal_count * sizeof(SearchResult));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < literal_count; i++) {
        if (literals[i] == NULL) {
            free(results);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        results[i].literal = (char *)literals[i];
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t literal_len = strlen(literals[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t text_len = strlen(text);
        
        if (literal_len > text_len) {
            results[i].found = false;
            results[i].position = 0;
            continue;
        }

        const char *pos = strstr(text, literals[i]);
        if (pos != NULL) {
            if ((size_t)(pos - text) > text_len) {
                results[i].found = false;
                results[i].position = 0;
            } else {
                results[i].found = true;
                results[i].position = (size_t)(pos - text);
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