#include <stdio.h>
#include <string.h>

int find_literal(const char *text, const char *pattern, int *location) {
    *location = -1;
    size_t text_len = strlen(text);
    size_t pattern_len = strlen(pattern);

    for (size_t i = 0; i <= text_len - pattern_len; ++i) {
        if (strncmp(&text[i], pattern, pattern_len) == 0) {
            *location = i;
            return 1;
        }
    }

    return 0;
}

int main() {
    const char *text = "This is a sample string to search for a literal.";
    const char *pattern = "sample";
    int location;

    if (find_literal(text, pattern, &location)) {
        printf("Pattern found at index: %d\n", location);
    } else {
        printf("Pattern not found.\n");
    }

    return 0;
}