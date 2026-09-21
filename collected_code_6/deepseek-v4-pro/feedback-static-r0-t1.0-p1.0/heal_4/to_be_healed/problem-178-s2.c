#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LITERAL_LENGTH 255

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char literal[MAX_LITERAL_LENGTH + 1];
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

        size_t len = strnlen(literals[i], MAX_LITERAL_LENGTH + 1);
        if (len > MAX_LITERAL_LENGTH) {
            free(results);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(results[i].literal, literals[i], MAX_LITERAL_LENGTH);
        results[i].literal[MAX_LITERAL_LENGTH] = '\0';
        
        const char *pos = strstr(text, literals[i]);
        if (pos != NULL) {
            results[i].found = true;
            results[i].position = (size_t)(pos - text);
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