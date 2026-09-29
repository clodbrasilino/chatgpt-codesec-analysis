#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *sub) {
    if (str == NULL || sub == NULL || sub[0] == '\0') {
        return false;
    }

    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);

    if (str_len % sub_len != 0) {
        return false;
    }

    for (size_t i = 0; i < str_len; i += sub_len) {
        if (strncmp(str + i, sub, sub_len) != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test_strings[][2] = {
        {"abcabcabc", "abc"},
        {"hellohello", "hello"},
        {"abcabcabd", "abc"},
        {"hello", "hell"},
        {"", "abc"},
        {"abc", ""},
        {"aaaaaa", "aa"},
        {"test", "test"}
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        printf("\"%s\" is concatenation of \"%s\": %s\n",
               test_strings[i][0],
               test_strings[i][1],
               is_concatenation(test_strings[i][0], test_strings[i][1]) ? "true" : "false");
    }

    return 0;
}