#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_substrings(const char *text, size_t text_length,
                           const char *substring, size_t substring_length,
                           size_t **positions, size_t *occurrences)
{
    size_t position;
    size_t count = 0;
    size_t *result = NULL;

    if (text == NULL || substring == NULL ||
        positions == NULL || occurrences == NULL) {
        return -1;
    }

    *positions = NULL;
    *occurrences = 0;

    if (substring_length == 0 || substring_length > text_length) {
        return 0;
    }

    for (position = 0; position <= text_length - substring_length; ++position) {
        if (memcmp(text + position, substring, substring_length) == 0) {
            ++count;
        }
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    if (count != 0) {
        size_t index = 0;

        result = malloc(count * sizeof(*result));
        if (result == NULL) {
            return -1;
        }

        for (position = 0;
             position <= text_length - substring_length;
             ++position) {
            if (memcmp(text + position, substring, substring_length) == 0) {
                result[index++] = position;
            }
        }
    }

    *positions = result;
    *occurrences = count;
    return 0;
}

int main(void)
{
    static const char text[] = "abracadabra";
    static const char substring[] = "abra";
    size_t *positions = NULL;
    size_t occurrences = 0;
    size_t index;

    if (find_substrings(text, sizeof(text) - 1,
                        substring, sizeof(substring) - 1,
                        &positions, &occurrences) != 0) {
        fputs("Failed to find substrings.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Occurrences: %zu\n", occurrences);

    for (index = 0; index < occurrences; ++index) {
        printf("Position: %zu\n", positions[index]);
    }

    free(positions);
    return EXIT_SUCCESS;
}