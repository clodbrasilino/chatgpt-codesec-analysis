#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

static size_t max_uppercase_run(const char *str)
{
    size_t max_run = 0;
    size_t current_run = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
        str++;
    }

    return max_run;
}

int main(void)
{
    const char *tests[] = {
        "helloWORLDfooBAR",
        "ABCdefGHIJKLmno",
        "",
        "lowercase only",
        "ALLUPPERCASE",
        NULL
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        size_t result = max_uppercase_run(tests[i]);
        if (tests[i] != NULL) {
            if (printf("\"%s\" -> %zu\n", tests[i], result) < 0) {
                return 1;
            }
        } else {
            if (printf("(null) -> %zu\n", result) < 0) {
                return 1;
            }
        }
    }

    return 0;
}