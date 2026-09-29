#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int match_ab(const char *str)
{
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0U; str[i] != '\0'; i++) {
        if ((str[i] == 'a') && (str[i + 1U] == 'b')) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const char *tests[] = { "ab", "abc", "abbb", "a", "b", "aab", "ba", "" };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        if (match_ab(tests[i]) == 1) {
            if (printf("\"%s\": match\n", tests[i]) < 0) {
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