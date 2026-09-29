#include <stdio.h>
#include <string.h>

int find_literal(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t haystack_len = strlen(haystack);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t needle_len = strlen(needle);
    if (needle_len > haystack_len) {
        return -1;
    }
    for (size_t i = 0; i <= haystack_len - needle_len; ++i) {
        if (strncmp(&haystack[i], needle, needle_len) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int main() {
    const char *str = "This is a simple example";
    const char *pattern = "simple";
    int pos = find_literal(str, pattern);
    if (pos != -1) {
        printf("Pattern found at position: %d\n", pos);
    } else {
        printf("Pattern not found.\n");
    }
    return 0;
}