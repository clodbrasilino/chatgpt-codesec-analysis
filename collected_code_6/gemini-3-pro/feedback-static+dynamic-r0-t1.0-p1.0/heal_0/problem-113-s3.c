#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool is_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    if (*str == '-' || *str == '+') {
        str++;
    }

    if (*str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    const char *test_strings[] = {
        "12345",
        "-6789",
        "+42",
        "0",
        "  123",
        "12.3",
        "abc",
        "",
        "-",
        NULL
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            printf("\"%s\": %s\n", test_strings[i], is_integer(test_strings[i]) ? "true" : "false");
        } else {
            printf("NULL: %s\n", is_integer(test_strings[i]) ? "true" : "false");
        }
    }

    return 0;
}