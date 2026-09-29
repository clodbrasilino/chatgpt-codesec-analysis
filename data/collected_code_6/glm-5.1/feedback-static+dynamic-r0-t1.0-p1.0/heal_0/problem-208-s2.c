#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int is_valid_decimal(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[+-]?([0-9]+([.][0-9]{1,2})?|[.][0-9]{1,2})$", REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(void) {
    const char *test_cases[] = {
        "123.45",
        "0.99",
        "-42.10",
        ".50",
        "123",
        "12.3",
        "12.345",
        "abc",
        "12.",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("%s: %s\n", test_cases[i], is_valid_decimal(test_cases[i]) ? "Valid" : "Invalid");
    }

    return 0;
}