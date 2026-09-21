#include <stdio.h>
#include <string.h>

int count_occurrences(const char *str, const char *pattern, size_t str_len, size_t pattern_len) {
    int count = 0;
    if (pattern_len == 0 || str_len < pattern_len) return 0;

    for (const char *p = str; p <= str + str_len - pattern_len; p++) {
        if (memcmp(p, pattern, pattern_len) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    const char *str = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char *pattern = "std";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t pattern_len = strlen(pattern);
    int occurrences = count_occurrences(str, pattern, str_len, pattern_len);
    printf("The pattern '%s' occurs %d times.\n", pattern, occurrences);
    return 0;
}