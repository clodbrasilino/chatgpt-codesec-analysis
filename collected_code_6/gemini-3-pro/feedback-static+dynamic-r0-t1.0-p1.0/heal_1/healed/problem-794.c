#include <stdio.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    const char *first_a = NULL;
    const char *ptr = str;

    while (*ptr != '\0') {
        if (*ptr == 'a' && first_a == NULL) {
            first_a = ptr;
        }
        ptr++;
    }

    size_t len = ptr - str;
    if (len < 2) {
        return false;
    }

    if (first_a == NULL) {
        return false;
    }

    if (*(ptr - 1) == 'b') {
        const char *last_char = ptr - 1;
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