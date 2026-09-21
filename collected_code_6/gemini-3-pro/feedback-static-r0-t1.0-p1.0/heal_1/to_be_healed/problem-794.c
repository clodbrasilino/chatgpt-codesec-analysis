#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 2) {
        return false;
    }

    const char *first_a = strchr(str, 'a');
    if (first_a == NULL) {
        return false;
    }

    if (str[len - 1] == 'b') {
        const char *last_char = &str[len - 1];
        if (first_a < last_char) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test_strings[] = {
        "axyzb",
        "ab",
        "xyzab",
        "a",
        "b",
        "ba",
        "abc",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; ++i) {
        bool result = match_pattern(test_strings[i]);
        if (result) {
            printf("\"%s\" : Match\n", test_strings[i]);
        } else {
            printf("\"%s\" : No Match\n", test_strings[i]);
        }
    }

    return 0;
}