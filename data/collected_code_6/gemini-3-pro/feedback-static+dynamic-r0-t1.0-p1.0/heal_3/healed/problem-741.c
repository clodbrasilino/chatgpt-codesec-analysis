#include <stdio.h>
#include <stdbool.h>

bool are_all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    char first_char = *str;
    str++;

    while (*str != '\0') {
        if (*str != first_char) {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    const char *tests[] = {
        "aaaaa",
        "aabbb",
        "a",
        "",
        NULL
    };

    for (int i = 0; i < 5; i++) {
        if (are_all_characters_same(tests[i])) {
            printf("test%d: All characters are the same.\n", i + 1);
        } else {
            printf("test%d: Characters are not all the same.\n", i + 1);
        }
    }

    return 0;
}