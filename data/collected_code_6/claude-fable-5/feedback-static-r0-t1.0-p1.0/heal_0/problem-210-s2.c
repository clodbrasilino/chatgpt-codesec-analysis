#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_allowed_characters(const char *str, int *result);

int is_allowed_characters(const char *str, int *result)
{
    regex_t regex;
    int ret;

    if (str == NULL || result == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        *result = 1;
        return 0;
    } else if (ret == REG_NOMATCH) {
        *result = 0;
        return 0;
    }

    return -1;
}

int main(void)
{
    const char *tests[] = {
        "HelloWorld123",
        "hello_world",
        "abc",
        "ABC999",
        "with space",
        ""
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < count; i++) {
        int result = 0;
        if (is_allowed_characters(tests[i], &result) != 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\" contains only allowed characters\n", tests[i]);
        } else {
            printf("\"%s\" contains disallowed characters\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}