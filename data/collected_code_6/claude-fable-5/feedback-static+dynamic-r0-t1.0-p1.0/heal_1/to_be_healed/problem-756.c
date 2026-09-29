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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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