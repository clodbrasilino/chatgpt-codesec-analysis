#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool match_a_anything_b(const char *str)
{
    size_t len;
    const char *first_a;

    if (str == NULL) {
        return false;
    }

    len = strlen(str);
    if (len < 2) {
        return false;
    }

    first_a = strchr(str, 'a');
    if (first_a == NULL) {
        return false;
    }

    if (str[len - 1] != 'b') {
        return false;
    }

    if (first_a >= &str[len - 1]) {
        return false;
    }

    return true;
}

int main(void)
{
    const char *tests[] = {
        "ab",
        "axyzb",
        "a123b",
        "b",
        "a",
        "ba",
        "xxaxxb",
        "aab",
        "",
        "abc"
    };
    size_t count;
    size_t i;

    count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        if (match_a_anything_b(tests[i])) {
            if (printf("\"%s\" matches\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("\"%s\" does not match\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}