#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_binary_string(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t length = strlen(str);
    if (length == 0) {
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test_cases[] = {
        "101010",
        "102010",
        "000",
        "111",
        "2",
        "",
        NULL
    };

    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        bool result = is_binary_string(test_cases[i]);
        if (test_cases[i] != NULL) {
            printf("\"%s\" -> %s\n", test_cases[i], result ? "true" : "false");
        } else {
            printf("NULL -> %s\n", result ? "true" : "false");
        }
    }

    return 0;
}