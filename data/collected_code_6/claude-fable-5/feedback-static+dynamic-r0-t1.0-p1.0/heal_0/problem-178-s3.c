#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    const char *literal;
    size_t position;
    int found;
} SearchResult;

int search_literals(const char *text, const char *const *literals,
                    size_t literal_count, SearchResult *results)
{
    size_t i;

    if (text == NULL || literals == NULL || results == NULL) {
        return -1;
    }

    for (i = 0; i < literal_count; i++) {
        const char *match;

        results[i].literal = literals[i];
        results[i].position = 0;
        results[i].found = 0;

        if (literals[i] == NULL || literals[i][0] == '\0') {
            continue;
        }

        match = strstr(text, literals[i]);
        if (match != NULL) {
            results[i].found = 1;
            results[i].position = (size_t)(match - text);
        }
    }

    return 0;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *const literals[] = { "quick", "fox", "cat", "lazy" };
    size_t literal_count = sizeof(literals) / sizeof(literals[0]);
    SearchResult *results;
    size_t i;
    int status;

    results = malloc(literal_count * sizeof(*results));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = search_literals(text, literals, literal_count, results);
    if (status != 0) {
        fprintf(stderr, "Search failed due to invalid arguments\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < literal_count; i++) {
        if (results[i].found) {
            printf("Found \"%s\" at position %zu\n",
                   results[i].literal, results[i].position);
        } else {
            printf("\"%s\" not found\n", results[i].literal);
        }
    }

    free(results);
    return EXIT_SUCCESS;
}