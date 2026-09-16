#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_decimal(const char *str) {
    regex_t regex;
    int ret;
    const char *pattern = "^[+-]?([0-9]+([.][0-9]{1,2})?|[.][0-9]{1,2})$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(void) {
    const char *test_values[] = {
        "123",
        "-123.45",
        "+123.4",
        "123.456",
        ".",
        ".5",
        "1.",
        "abc",
        "",
        "12.3.4"
    };
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        printf("%s: %s\n", test_values[i], is_valid_decimal(test_values[i]) ? "valid" : "invalid");
    }

    return 0;
}