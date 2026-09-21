#include <stdio.h>
#include <string.h>

int match_pattern(const char *str, size_t len) {
    if (len == 0 || str[0] != 'a') {
        return 0;
    }
    if (len == 1 || (len == 2 && (str[1] == 'b' || str[1] == '\0'))) {
        return 1;
    }
    return 0;
}

int main() {
    const char *test_strings[] = {"a", "ab", "abc", "b", "ac", "aa", "", "bb"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(test_strings[i]);
        printf("%s: %s\n", test_strings[i], match_pattern(test_strings[i], len) ? "Match" : "No Match");
    }

    return 0;
}