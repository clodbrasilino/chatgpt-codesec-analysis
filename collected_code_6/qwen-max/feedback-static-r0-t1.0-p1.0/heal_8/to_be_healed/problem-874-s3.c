#include <stdio.h>
#include <string.h>

int is_concatenated(const char *str, const char *substr) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(substr);
    if (len == 0 || len > (size_t)-1 / sizeof(char)) return 0;

    while (*str) {
        size_t i = 0;
        for (; i < len && *(str + i) == substr[i]; i++)
            if (substr[i] == '\0') return 0;
        if (i == len) {
            if (str[i] == '\0' || (i == 1 && str[i - 1] == '\0')) return 1;
            str += i - 1;
        }
        str++;
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