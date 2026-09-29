#include <stdio.h>
#include <stdbool.h>

bool match_pattern(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (str[len] != '\0') {
        return false;
    }

    if (len < 2) {
        return false;
    }

    if (str[0] != 'a') {
        return false;
    }

    if (str[len - 1] != 'b') {
        return false;
    }

    return true;
}

int main(void) {
    const char *test_cases[] = {
        "ab",
        "axyzb",
        "a123b",
        "b",
        "a",
        "ba",
        "abc",
        "cab",
        "",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; ++i) {
        bool result = match_pattern(test_cases[i], 1024);
        printf("\"%s\" -> %s\n", test_cases[i], result ? "true" : "false");
    }

    return 0;
}