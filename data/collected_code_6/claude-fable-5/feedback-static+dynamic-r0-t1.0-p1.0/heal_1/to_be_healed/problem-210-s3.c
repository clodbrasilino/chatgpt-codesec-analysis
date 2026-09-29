#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int contains_only_allowed_chars(const char *str)
{
    regex_t regex;
    int ret;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "Hello123",
        "abcXYZ",
        "hello world",
        "test!",
        "0123456789",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    for (i = 0; i < count; i++) {
        result = contains_only_allowed_chars(tests[i]);
        if (result == 1) {
            printf("\"%s\" -> valid\n", tests[i]);
        } else if (result == 0) {
            printf("\"%s\" -> invalid\n", tests[i]);
        } else {
            fprintf(stderr, "regex error while checking \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}