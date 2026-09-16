#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int starts_with_vowel(const char *str)
{
    regex_t regex;
    int ret;
    int result = 0;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED | REG_NOSUB);
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
    const char *tests[] = { "apple", "banana", "Orange", "umbrella", "grape", "" };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'res' can be reduced. [variableScope]
     */
    int res;

    for (i = 0; i < count; i++) {
        res = starts_with_vowel(tests[i]);
        if (res < 0) {
            fprintf(stderr, "Error processing string: \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (res == 1) {
            printf("\"%s\" starts with a vowel\n", tests[i]);
        } else {
            printf("\"%s\" does not start with a vowel\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}