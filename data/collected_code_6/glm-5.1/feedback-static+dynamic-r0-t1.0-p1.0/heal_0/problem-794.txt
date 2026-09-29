#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
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
        bool result = match_pattern(test_cases[i]);
        printf("\"%s\" -> %s\n", test_cases[i], result ? "true" : "false");
    }

    return 0;
}