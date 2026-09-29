#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int check_decimal_precision(const char *str)
{
    regex_t regex;
    int ret;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^-?[0-9]+\\.[0-9]{2}$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret != REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_cases[] = {
        "123.45",
        "-67.89",
        "0.00",
        "123.4",
        "123.456",
        "123",
        "abc.de",
        NULL
    };
    int i;

    for (i = 0; test_cases[i] != NULL; i++) {
        if (check_decimal_precision(test_cases[i])) {
            printf("\"%s\" is a valid decimal with precision 2\n", test_cases[i]);
        } else {
            printf("\"%s\" is NOT a valid decimal with precision 2\n", test_cases[i]);
        }
    }

    return 0;
}