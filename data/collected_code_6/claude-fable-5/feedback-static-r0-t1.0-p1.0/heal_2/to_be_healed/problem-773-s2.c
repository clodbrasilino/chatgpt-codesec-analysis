#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

size_t find_substring_occurrences(const char *text, const char *pattern,
                                  size_t **positions)
{
    size_t count;
    size_t capacity;
    size_t pattern_len;
    size_t *result;
    size_t *temp;
    const char *cursor;
    const char *found;

    if (text == NULL || pattern == NULL || positions == NULL) {
        if (positions != NULL) {
            *positions = NULL;
        }
        return 0U;
    }

    *positions = NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_len = strlen(pattern);
    if (pattern_len == 0U) {
        return 0U;
    }

    count = 0U;
    capacity = 8U;
    result = malloc(capacity * sizeof(size_t));
    if (result == NULL) {
        return 0U;
    }

    cursor = text;
    found = strstr(cursor, pattern);
    while (found != NULL) {
        if (count == capacity) {
            if (capacity > (SIZE_MAX / (2U * sizeof(size_t)))) {
                free(result);
                *positions = NULL;
                return 0U;
            }
            capacity *= 2U;
            temp = realloc(result, capacity * sizeof(size_t));
            if (temp == NULL) {
                free(result);
                *positions = NULL;
                return 0U;
            }
            result = temp;
        }
        result[count] = (size_t)(found - text);
        count++;
        cursor = found + 1;
        found = strstr(cursor, pattern);
    }

    if (count == 0U) {
        free(result);
        *positions = NULL;
        return 0U;
    }

    *positions = result;
    return count;
}

int main(void)
{
    const char *text = "the cat sat on the mat, the end";
    const char *pattern = "the";
    size_t *positions = NULL;
    size_t count;
    size_t i;

    count = find_substring_occurrences(text, pattern, &positions);

    if (count == 0U || positions == NULL) {
        if (printf("Substring \"%s\" not found in \"%s\"\n",
                   pattern, text) < 0) {
            free(positions);
            return EXIT_FAILURE;
        }
        free(positions);
        return EXIT_SUCCESS;
    }

    if (printf("Substring \"%s\" found %zu time(s) in \"%s\"\n",
               pattern, count, text) < 0) {
        free(positions);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("Occurrence %zu at position %zu\n",
                   i + 1U, positions[i]) < 0) {
            free(positions);
            return EXIT_FAILURE;
        }
    }

    free(positions);
    return EXIT_SUCCESS;
}