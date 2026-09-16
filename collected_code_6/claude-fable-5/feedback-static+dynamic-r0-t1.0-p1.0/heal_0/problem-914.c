#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_two_alternating(const char *str)
{
    size_t len;
    size_t i;
    char first;
    char second;

    if (str == NULL) {
        return false;
    }

    len = strlen(str);
    if (len < 2U) {
        return false;
    }

    first = str[0];
    second = str[1];

    if (first == second) {
        return false;
    }

    for (i = 2U; i < len; i++) {
        if ((i % 2U) == 0U) {
            if (str[i] != first) {
                return false;
            }
        } else {
            if (str[i] != second) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    const char *tests[] = {
        "ababab",
        "xyxyxyxy",
        "aaaa",
        "abcabc",
        "ab",
        "a",
        "",
        "abab a"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        if (is_two_alternating(tests[i])) {
            if (printf("\"%s\" -> yes\n", tests[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\" -> no\n", tests[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}