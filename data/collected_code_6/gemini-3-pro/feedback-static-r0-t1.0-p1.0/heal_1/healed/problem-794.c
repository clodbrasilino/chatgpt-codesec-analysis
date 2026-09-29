#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strnlen(str, MAX_STR_LEN);
    if (len < 2 || len == MAX_STR_LEN) {
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