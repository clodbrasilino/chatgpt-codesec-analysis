#include <stdio.h>
#include <string.h>

void find_substrings(const char *str, const char *substr) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int substr_len = strlen(substr);
    for (int i = 0; i <= str_len - substr_len; i++) {
        if (strncmp(&str[i], substr, substr_len) == 0) {
            printf("Found at position: %d\n", i);
        }
    }
}

int main() {
    const char *str = "This is a test string to test substring search.";
    const char *substr = "test";
    find_substrings(str, substr);
    return 0;
}