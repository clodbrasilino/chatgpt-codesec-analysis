#include <stdio.h>
#include <stdbool.h>

bool match_pattern(const char *str, size_t len) {
    if (str == NULL || len < 2) {
        return false;
    }

    bool found_a = false;
    size_t last_b_pos = len;
    size_t first_a_pos = len;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == 'a') {
            if (!found_a) {
                first_a_pos = i;
            }
            found_a = true;
        }
        if (str[i] == 'b') {
            last_b_pos = i;
        }
    }

    if (!found_a || last_b_pos == len) {
        return false;
    }

    return first_a_pos < last_b_pos;
}

int main(void) {
    const char *test_strings[] = {
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

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        size_t len = 0;
        while (test_strings[i][len] != '\0') {
            len++;
        }
        bool result = match_pattern(test_strings[i], len);
        printf("String: %-10s Matches: %s\n", test_strings[i], result ? "true" : "false");
    }

    return 0;
}