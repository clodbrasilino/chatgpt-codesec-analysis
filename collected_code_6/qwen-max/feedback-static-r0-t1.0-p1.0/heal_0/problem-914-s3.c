#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_alternating(const char *str) {
    int len = strlen(str);
    if (len <= 1) return false;

    char first_char = str[0];
    char second_char = str[1];

    if (first_char == second_char) return false;

    for (int i = 2; i < len; ++i) {
        if (i % 2 == 0 && str[i] != first_char) return false;
        if (i % 2 != 0 && str[i] != second_char) return false;
    }

    return true;
}

int main() {
    const char *test_strings[] = {"ababab", "aba", "abc", "a", "", "aa"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; ++i) {
        printf("%s: %s\n", test_strings[i], is_alternating(test_strings[i]) ? "true" : "false");
    }

    return 0;
}