#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_characters_same(const char *str)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return true;
    }

    for (i = 1U; str[i] != '\0'; i++) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *tests[] = {
        "aaaa",
        "abcd",
        "1111",
        "a",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        if (all_characters_same(tests[i])) {
            if (printf("\"%s\": all characters are same\n", tests[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\": all characters are not same\n", tests[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}