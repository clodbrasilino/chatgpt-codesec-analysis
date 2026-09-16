#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int match_a_followed_by_three_b(const char *text)
{
    size_t len;
    size_t i;

    if (text == NULL) {
        return 0;
    }

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
        "aabbbbc",
        "abb",
        "acb",
        "xyzabbbxyz",
        ""
    };
    size_t count;
    size_t i;

    count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        if (match_a_followed_by_three_b(tests[i]) == 1) {
            if (printf("Match found: %s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("No match: %s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}