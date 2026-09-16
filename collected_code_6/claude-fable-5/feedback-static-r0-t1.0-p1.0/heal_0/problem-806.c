#include <stdio.h>
#include <stdlib.h>
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
        "nouppercase",
        "ALLUPPERCASE",
        ""
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        size_t result = max_uppercase_run(tests[i]);
        if (printf("Input: \"%s\" -> Max uppercase run: %zu\n",
                   tests[i], result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}