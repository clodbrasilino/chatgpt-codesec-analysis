#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_a_optional_b(const char *text)
{
    size_t i;
    size_t len;

    if (text == NULL) {
        return false;
    }

    len = strlen(text);

    for (i = 0; i < len; i++) {
        if (text[i] == 'a') {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const char *tests[] = {
        "ac",
        "abc",
        "abbc",
        "bbc",
        "a",
        "ab",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (match_a_optional_b(tests[i])) {
            if (printf("\"%s\": Match found\n", tests[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\": No match\n", tests[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}