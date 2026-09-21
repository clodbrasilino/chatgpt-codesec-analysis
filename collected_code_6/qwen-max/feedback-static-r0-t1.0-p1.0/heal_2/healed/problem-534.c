#include <stdio.h>
#include <string.h>

int find_literal(const char *text, const char *pattern, int *location) {
    if (text == NULL || pattern == NULL) {
        return -1;
    }
    *location = 0;
    size_t pattern_len = strlen(pattern);
    size_t text_len = strlen(text);
    for (size_t index = 0; index <= text_len - pattern_len; ++index) {
        if (strncmp(&text[index], pattern, pattern_len) == 0) {
            *location = index;
            return 1;
        }
    }
    return -1;
}

int main() {
    const char *text = "Hello, World!";
    const char *pattern = "World";
    int location;

    if (find_literal(text, pattern, &location) > 0) {
        printf("Pattern found at index: %d\n", location);
    } else {
        printf("Pattern not found.\n");
    }

    return 0;
}