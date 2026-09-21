#include <stdio.h>
#include <string.h>

int find_literal(const char *text, size_t text_len, const char *pattern, size_t pattern_len, int *location) {
    if (text == NULL || pattern == NULL) {
        return -1;
    }
    *location = 0;
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t pattern_len = strlen(pattern);

    if (find_literal(text, text_len, pattern, pattern_len, &location) > 0) {
        printf("Pattern found at index: %d\n", location);
    } else {
        printf("Pattern not found.\n");
    }

    return 0;
}