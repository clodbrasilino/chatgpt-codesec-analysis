#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_literals(const char *haystack, const char **literals, size_t count) {
    if (haystack == NULL || literals == NULL) {
        return -1;
    }

    size_t i;
    for (i = 0; i < count; i++) {
        if (literals[i] == NULL) {
            continue;
        }

        const char *found = strstr(haystack, literals[i]);
        if (found != NULL) {
            return (int)i;
        }
    }

    return -1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. Price: $100. [Tag]";
    const char *literals[] = {
        "quick",
        "$100",
        "[Tag]",
        "missing"
    };
    size_t count = sizeof(literals) / sizeof(literals[0]);

    int result = search_literals(text, literals, count);
    if (result >= 0) {
        printf("Found literal at index %d: %s\n", result, literals[result]);
    } else {
        printf("No literals found or error occurred.\n");
    }

    return 0;
}