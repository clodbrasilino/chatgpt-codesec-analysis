#include <stdio.h>
#include <string.h>

int match_a_followed_by_optional_b(const char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);

    for (i = 0; i < len; i++) {
        if (str[i] == 'a') {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const char *tests[] = { "ab", "a", "abc", "ac", "bb", "", "bab" };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (match_a_followed_by_optional_b(tests[i])) {
            if (printf("\"%s\" -> match\n", tests[i]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\" -> no match\n", tests[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}