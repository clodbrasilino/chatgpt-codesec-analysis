#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_allowed_characters(const char *str)
{
    regex_t regex;
    int ret;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        result = -1;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "HelloWorld123",
        "abc_def",
        "Test!",
        "0123456789",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    for (i = 0; i < count; i++) {
        status = is_allowed_characters(tests[i]);
        if (status < 0) {
            fprintf(stderr, "Regex error while checking \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (status == 1) {
            printf("\"%s\" contains only allowed characters\n", tests[i]);
        } else {
            printf("\"%s\" contains disallowed characters\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}