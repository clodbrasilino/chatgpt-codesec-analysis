#include <stdio.h>
#include <string.h>

int match_string(const char *str, size_t str_len) {
    if (str_len != 4) {
        return 0;
    }
    return (str[0] == 'a' && str[1] == 'b' && str[2] == 'b' && str[3] == '\0');
}

int main() {
    const char *test_strings[] = {"abbb", "aabb", "abbbb", "abc", "aabbb"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(test_strings[i]);
        if (match_string(test_strings[i], len)) {
            printf("Match: %s\n", test_strings[i]);
        } else {
            printf("No match: %s\n", test_strings[i]);
        }
    }
    return 0;
}