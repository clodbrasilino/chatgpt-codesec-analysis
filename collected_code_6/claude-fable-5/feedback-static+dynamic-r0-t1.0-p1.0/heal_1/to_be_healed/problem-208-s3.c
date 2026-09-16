#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_decimal_precision_two(const char *input);

int is_decimal_precision_two(const char *input)
{
    regex_t regex;
    int ret;
    int result = 0;

    if (input == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[+-]?[0-9]+\\.[0-9]{2}$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, input, 0, NULL, 0);
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
        "123.45",
        "-0.99",
        "+10.00",
        "123.456",
        "123.4",
        "abc.12",
        "123",
        ".45"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'check' can be reduced. [variableScope]
     */
    int check;

    for (i = 0; i < count; i++) {
        check = is_decimal_precision_two(tests[i]);
        if (check < 0) {
            fprintf(stderr, "Regex error while checking: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (check == 1) {
            printf("%s : valid decimal with precision 2\n", tests[i]);
        } else {
            printf("%s : invalid\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}