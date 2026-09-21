#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_alternating(const char *str)
{
    size_t len;
    size_t i;

    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len < 2U) {
        return false;
    }

    if (str[0] == str[1]) {
        return false;
    }

    for (i = 2U; i < len; i++) {
        if (str[i] != str[i - 2U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *tests[] = {
        "ababab",
        "xyxyxy",
        "aaaa",
        "abcabc",
        "ab",
        "a",
        "",
        "xyxyx"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        if (is_alternating(tests[i])) {
            if (printf("\"%s\": yes\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("\"%s\": no\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}