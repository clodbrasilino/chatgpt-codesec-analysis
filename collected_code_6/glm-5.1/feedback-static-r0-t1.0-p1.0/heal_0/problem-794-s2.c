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

    bool found_a = false;
    size_t last_b_pos = len;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == 'a') {
            found_a = true;
        }
        if (str[i] == 'b') {
            last_b_pos = i;
        }
    }

    if (!found_a || last_b_pos == len) {
        return false;
    }

    size_t first_a_pos = len;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == 'a') {
            first_a_pos = i;
            break;
        }
    }

    return first_a_pos < last_b_pos;
}

int main(void) {
    const char *test_cases[] = {
        "acdb",
        "ab",
        "aab",
        "acb",
        "a123b",
        "bca",
        "a",
        "b",
        "ba",
        "cab",
        "abc",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        bool result = match_pattern(test_cases[i]);
        printf("String: %-10s Matches: %s\n", test_cases[i], result ? "true" : "false");
    }

    return 0;
}