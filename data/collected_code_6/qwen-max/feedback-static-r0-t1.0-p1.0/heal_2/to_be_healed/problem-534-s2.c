#include <stdio.h>
#include <string.h>

int find_literal(const char *text, size_t text_len, const char *pattern, size_t pattern_len, int *location) {
    *location = -1;
    if (text == NULL || pattern == NULL || text_len < pattern_len) return 0;
    
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t pattern_len = strlen(pattern);

    if (find_literal(text, text_len, pattern, pattern_len, &location)) {
        printf("Pattern found at index: %d\n", location);
    } else {
        printf("Pattern not found.\n");
    }

    return 0;
}