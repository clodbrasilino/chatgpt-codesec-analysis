#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t find_substrings(const char *text, const char *substring,
                              size_t **positions)
{
    size_t count = 0;
    size_t capacity = 0;
    size_t *result = NULL;
    const char *match;
    const char *cursor;

    if (text == NULL || substring == NULL || positions == NULL) {
        return 0;
    }

    *positions = NULL;

    if (*substring == '\0') {
        return 0;
    }

    cursor = text;

    while ((match = strstr(cursor, substring)) != NULL) {
        if (count == capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
            size_t *new_result;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof(*result)) {
                free(result);
                return 0;
            }

            new_result = realloc(result, new_capacity * sizeof(*result));
            if (new_result == NULL) {
                free(result);
                return 0;
            }

            result = new_result;
            capacity = new_capacity;
        }

        result[count++] = (size_t)(match - text);
        cursor = match + 1;
    }

    *positions = result;
    return count;
}

int main(void)
{
    char text[1024];
    char substring[256];
    size_t *positions = NULL;
    size_t count;
    size_t i;

    if (fgets(text, sizeof(text), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(substring, sizeof(substring), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    text[strcspn(text, "\n")] = '\0';
    substring[strcspn(substring, "\n")] = '\0';

    if (substring[0] == '\0') {
        return EXIT_FAILURE;
    }

    count = find_substrings(text, substring, &positions);

    printf("Occurrences: %zu\n", count);

    for (i = 0; i < count; ++i) {
        printf("Position: %zu\n", positions[i]);
    }

    free(positions);
    return EXIT_SUCCESS;
}