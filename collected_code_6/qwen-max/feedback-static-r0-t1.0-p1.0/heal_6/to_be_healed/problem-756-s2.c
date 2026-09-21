#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_ab(const char *str, size_t len) {
    if (len > 0 && str[0] == 'a') {
        if (len == 1 || (len == 2 && str[1] == 'b')) {
            return true;
        }
    }
    return false;
}

int main() {
    const char* test_strings[] = {"a", "ab", "ac", "abc", "b", ""};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        printf("Testing '%s': %s\n", test_strings[i], match_ab(test_strings[i], strlen(test_strings[i])) ? "Match" : "No Match");
    }
    return 0;
}