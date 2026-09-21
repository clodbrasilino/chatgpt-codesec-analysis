#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t find_substring_occurrences(const char *text, const char *pattern, size_t **positions)
{
    size_t count = 0;
    size_t capacity = 8;
    size_t text_len;
    size_t pattern_len;
    const char *cursor;
    size_t *result;
    size_t *temp;

    if (text == NULL || pattern == NULL || positions == NULL) {
        return 0;
    }

    *positions = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_len = strlen(pattern);

    if (pattern_len == 0 || pattern_len > text_len) {
        return 0;
    }

    result = malloc(capacity * sizeof(size_t));
    if (result == NULL) {
        return 0;
    }

    cursor = text;
    while ((cursor = strstr(cursor, pattern)) != NULL) {
        if (count == capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(size_t))) {
                free(result);
                *positions = NULL;
                return 0;
            }
            capacity *= 2;
            temp = realloc(result, capacity * sizeof(size_t));
            if (temp == NULL) {
                free(result);
                *positions = NULL;
                return 0;
            }
            result = temp;
        }
        result[count] = (size_t)(cursor - text);
        count++;
        cursor++;
    }

    if (count == 0) {
        free(result);
        *positions = NULL;
        return 0;
    }

    *positions = result;
    return count;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog near the river";
    const char *pattern = "the";
    size_t *positions = NULL;
    size_t count;
    size_t i;

    count = find_substring_occurrences(text, pattern, &positions);

    if (count == 0) {
        printf("Substring \"%s\" not found in the text.\n", pattern);
        return EXIT_SUCCESS;
    }

    printf("Substring \"%s\" found %zu time(s) at position(s):\n", pattern, count);
    for (i = 0; i < count; i++) {
        printf("  Position %zu\n", positions[i]);
    }

    free(positions);
    positions = NULL;

    return EXIT_SUCCESS;
}