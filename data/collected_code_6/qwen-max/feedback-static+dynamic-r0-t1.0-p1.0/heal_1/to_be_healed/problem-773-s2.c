#include <stdio.h>
#include <string.h>

void find_substrings(const char *str, const char *pattern) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int pattern_len = strlen(pattern);
    if (pattern_len == 0 || pattern_len > str_len) return;

    for (int i = 0; i <= str_len - pattern_len; i++) {
        if (strncmp(&str[i], pattern, pattern_len) == 0) {
            printf("Substring found at position: %d\n", i);
        }
    }
}

int main() {
    const char *text = "This is a test string to find the substring test in this text.";
    const char *substr = "test";
    find_substrings(text, substr);
    return 0;
}