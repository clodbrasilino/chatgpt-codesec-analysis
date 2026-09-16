#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_chars_same(const char *str)
{
    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return true;
    }

    size_t i = 1U;
    while (str[i] != '\0') {
        if (str[i] != str[0]) {
            return false;
        }
        i++;
    }

    return true;
}

int main(void)
{
    const char *tests[] = {
        "aaaa",
        "abca",
        "z",
        "",
        "bbbbbb",
        "bbbcbb"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0U; i < count; i++) {
        if (all_chars_same(tests[i])) {
            if (printf("\"%s\": all characters are same\n", tests[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\": not all characters are same\n", tests[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}