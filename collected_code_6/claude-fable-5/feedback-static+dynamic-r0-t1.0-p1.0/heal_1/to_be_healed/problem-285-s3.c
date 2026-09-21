#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_a_followed_by_bb(const char *text)
{
    size_t i;
    size_t len;

    if (text == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(text);

    for (i = 0; i < len; i++) {
        if (text[i] == 'a') {
            size_t count = 0;
            size_t j = i + 1;

            while (j < len && text[j] == 'b' && count < 3) {
                count++;
                j++;
            }

            if (count >= 2 && count <= 3) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const char *tests[] = {
        "abb",
        "abbb",
        "abbbb",
        "ab",
        "aabbc",
        "xyz",
        "aabbbbc",
        ""
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        int result = match_a_followed_by_bb(tests[i]);
        if (printf("\"%s\" -> %s\n", tests[i], result ? "match" : "no match") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}