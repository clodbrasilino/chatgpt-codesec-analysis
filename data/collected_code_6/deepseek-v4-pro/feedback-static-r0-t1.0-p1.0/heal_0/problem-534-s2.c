#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_literal(const char *haystack, const char *needle, int *location) {
    if (haystack == NULL || needle == NULL || location == NULL) {
        return -1;
    }

    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);

    if (needle_len == 0) {
        *location = 0;
        return 0;
    }

    if (needle_len > haystack_len) {
        return -1;
    }

    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        if (strncmp(haystack + i, needle, needle_len) == 0) {
            *location = (int)i;
            return 0;
        }
    }

    return -1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown";
    int position = -1;

    int result = search_literal(text, pattern, &position);

    if (result == 0) {
        printf("Pattern found at position %d\n", position);
    } else {
        printf("Pattern not found\n");
    }

    pattern = "fox";
    position = -1;
    result = search_literal(text, pattern, &position);

    if (result == 0) {
        printf("Pattern found at position %d\n", position);
    } else {
        printf("Pattern not found\n");
    }

    pattern = "cat";
    position = -1;
    result = search_literal(text, pattern, &position);

    if (result == 0) {
        printf("Pattern found at position %d\n", position);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}