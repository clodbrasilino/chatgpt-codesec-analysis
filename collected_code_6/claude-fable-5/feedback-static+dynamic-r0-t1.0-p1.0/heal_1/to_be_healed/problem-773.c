#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    size_t *positions;
    size_t count;
} SearchResult;

int find_substring_occurrences(const char *text, const char *pattern, SearchResult *result)
{
    const char *current;
    size_t pattern_len;
    size_t capacity;
    size_t *temp;

    if (text == NULL || pattern == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_len = strlen(pattern);
    if (pattern_len == 0) {
        return -1;
    }

    result->positions = NULL;
    result->count = 0;
    capacity = 0;

    current = strstr(text, pattern);
    while (current != NULL) {
        if (result->count == capacity) {
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            temp = realloc(result->positions, new_capacity * sizeof(size_t));
            if (temp == NULL) {
                free(result->positions);
                result->positions = NULL;
                result->count = 0;
                return -1;
            }
            result->positions = temp;
            capacity = new_capacity;
        }
        result->positions[result->count] = (size_t)(current - text);
        result->count++;
        current = strstr(current + 1, pattern);
    }

    return 0;
}

void free_search_result(SearchResult *result)
{
    if (result != NULL) {
        free(result->positions);
        result->positions = NULL;
        result->count = 0;
    }
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog, the end";
    const char *pattern = "the";
    SearchResult result;
    size_t i;

    if (find_substring_occurrences(text, pattern, &result) != 0) {
        fprintf(stderr, "Error: search failed\n");
        return EXIT_FAILURE;
    }

    printf("Text: \"%s\"\n", text);
    printf("Pattern: \"%s\"\n", pattern);
    printf("Occurrences: %zu\n", result.count);

    for (i = 0; i < result.count; i++) {
        printf("Occurrence %zu at position %zu\n", i + 1, result.positions[i]);
    }

    free_search_result(&result);

    return EXIT_SUCCESS;
}