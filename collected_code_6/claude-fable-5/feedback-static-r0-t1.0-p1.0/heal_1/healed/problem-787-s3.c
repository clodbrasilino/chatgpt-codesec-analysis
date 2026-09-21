#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_LEN 4096

int match_a_followed_by_three_b(const char *text, size_t max_len)
{
    size_t i;
    size_t len;

    if (text == NULL) {
        return 0;
    }

    len = 0;
    while (len < max_len && text[len] != '\0') {
        len++;
    }

    if (len < 4) {
        return 0;
    }

    for (i = 0; i + 3 < len; i++) {
        if (text[i] == 'a' &&
            text[i + 1] == 'b' &&
            text[i + 2] == 'b' &&
            text[i + 3] == 'b') {
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
        "bbba",
        "xyzabbbxyz",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (match_a_followed_by_three_b(tests[i], MAX_TEXT_LEN)) {
            if (printf("\"%s\": match found\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("\"%s\": no match\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}