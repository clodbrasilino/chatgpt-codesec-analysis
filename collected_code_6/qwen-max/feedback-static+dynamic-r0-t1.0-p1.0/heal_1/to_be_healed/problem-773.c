#include <stdio.h>
#include <string.h>

void find_substrings(const char *text, const char *pattern) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t pattern_len = strlen(pattern);
    for (size_t i = 0; i <= text_len - pattern_len; i++) {
        if (strncmp(&text[i], pattern, pattern_len) == 0) {
            printf("Found '%s' at position %zu\n", pattern, i);
        }
    }
}

int main() {
    const char *text = "This is a test string to find substrings in a string";
    const char *pattern = "string";
    find_substrings(text, pattern);
    return 0;
}