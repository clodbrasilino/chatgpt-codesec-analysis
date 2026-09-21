#include <stdio.h>
#include <string.h>

int is_concatenated(const char *str, const char *substr) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(substr);
    if (len == 0 || !str) return 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    for (const char *p = str; p <= str + str_len - len; p++) {
        if (strncmp(p, substr, len) == 0) {
            if (p[len] == '\0' || (p + len < str + str_len && *(p + len) == '\0')) return 1;
            p += len - 1;
        }
    }
    return 0;
}

int main() {
    const char *str = "ababab";
    const char *substr = "ab";
    if (is_concatenated(str, substr)) {
        printf("The string is a concatenation of the substring.\n");
    } else {
        printf("The string is not a concatenation of the substring.\n");
    }
    return 0;
}