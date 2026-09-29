#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_substrings(const char *text, const char *substring,
                           size_t **positions, size_t *count)
{
    size_t text_length;
    size_t substring_length;
    size_t capacity = 0;
    size_t *result = NULL;

    if (text == NULL || substring == NULL || positions == NULL || count == NULL) {
        return -1;
    }

    *positions = NULL;
    *count = 0;

    text_length = strlen(text);
    substring_length = strlen(substring);

    if (substring_length == 0 || substring_length > text_length) {
        return 0;
    }

    for (size_t i = 0; i <= text_length - substring_length; ++i) {
        if (memcmp(text + i, substring, substring_length) == 0) {
            if (*count == capacity) {
                size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
                size_t *temporary;

                if (new_capacity < capacity ||
                    new_capacity > SIZE_MAX / sizeof(*result)) {
                    free(result);
                    return -1;
                }

                temporary = realloc(result, new_capacity * sizeof(*result));
                if (temporary == NULL) {
                    free(result);
                    return -1;
                }

                result = temporary;
                capacity = new_capacity;
            }

            result[*count] = i;
            ++(*count);
        }
    }

    *positions = result;
    return 0;
}

int main(void)
{
    const char *text = "abracadabra";
    const char *substring = "abra";
    size_t *positions = NULL;
    size_t count = 0;

    if (find_substrings(text, substring, &positions, &count) != 0) {
        fputs("Failed to find substrings.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Occurrences: %zu\n", count);

    for (size_t i = 0; i < count; ++i) {
        printf("Position: %zu\n", positions[i]);
    }

    free(positions);
    return EXIT_SUCCESS;
}