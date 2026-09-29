#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_string(const char *haystack, const char *needle, size_t *position)
{
    const char *found;

    if (haystack == NULL || needle == NULL || position == NULL) {
        return -1;
    }

    if (needle[0] == '\0') {
        return -1;
    }

    found = strstr(haystack, needle);
    if (found == NULL) {
        return 0;
    }

    *position = (size_t)(found - haystack);
    return 1;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown fox";
    size_t position = 0;
    int result;

    result = search_string(text, pattern, &position);

    if (result < 0) {
        if (fprintf(stderr, "Invalid input provided.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (result == 0) {
        if (printf("Pattern \"%s\" not found in the string.\n", pattern) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Pattern \"%s\" found at position %zu.\n", pattern, position) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}