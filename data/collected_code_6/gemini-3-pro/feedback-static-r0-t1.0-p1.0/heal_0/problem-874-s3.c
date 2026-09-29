#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_concatenation(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len < 2) {
        return 0;
    }

    for (size_t sub_len = 1; sub_len <= len / 2; ++sub_len) {
        if (len % sub_len == 0) {
            int match = 1;
            for (size_t i = sub_len; i < len; ++i) {
                if (str[i] != str[i % sub_len]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    const char *test_strings[] = {
        "abab",
        "abcabcabc",
        "abcd",
        "a",
        "",
        "aaaa",
        NULL
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        const char *current = test_strings[i];
        int result = is_concatenation(current);
        if (current == NULL) {
            printf("NULL -> %d\n", result);
        } else {
            printf("\"%s\" -> %d\n", current, result);
        }
    }

    return EXIT_SUCCESS;
}