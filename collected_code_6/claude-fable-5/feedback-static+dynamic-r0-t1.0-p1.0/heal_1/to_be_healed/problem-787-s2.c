#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int match_abbb(const char *text)
{
    size_t len;
    size_t i;

    if (text == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(text);
    if (len < 4U) {
        return 0;
    }

    for (i = 0U; i + 3U < len; i++) {
        if ((text[i] == 'a') &&
            (text[i + 1U] == 'b') &&
            (text[i + 2U] == 'b') &&
            (text[i + 3U] == 'b')) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const char *tests[] = {
        "abbb",
        "aabbbcc",
        "abb",
        "acb",
        "xyzabbbxyz",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        if (match_abbb(tests[i]) == 1) {
            if (printf("\"%s\" -> match\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("\"%s\" -> no match\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}