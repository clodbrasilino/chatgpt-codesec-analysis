#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_ab(const char *str) {
    if (str == NULL) return false;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        if (str[i] != 'a' && (i == 0 || str[i-1] != 'a')) return false;
        if (str[i] != 'b' && (i == 0 || str[i-1] != 'a')) return false;
    }
    return true;
}

int main() {
    const char *test_strings[] = {
        "a", "ab", "aab", "abb", "b", "ac", "abc"
    };
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("'%s': %s\n", test_strings[i], match_ab(test_strings[i]) ? "Match" : "No Match");
    }
    return 0;
}