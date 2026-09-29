#include <stdio.h>
#include <regex.h>
#include <string.h>

int is_ending_with_alphanumeric(const char *str, size_t max_len) {
    regex_t regex;
    int result;
    int ret = 0;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len == max_len) {
        return 0;
    }

    result = regcomp(&regex, "[a-zA-Z0-9]+$", REG_EXTENDED);
    if (result != 0) {
        return 0;
    }

    result = regexec(&regex, str, 0, NULL, 0);
    if (result == 0) {
        ret = 1;
    }

    regfree(&regex);
    return ret;
}

int main(void) {
    const char *test_strings[] = {
        "Hello123",
        "Hello@123",
        "Hello World1",
        "12345",
        "Hello!",
        "",
        "abcXYZ789"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    size_t max_len = 256;

    for (i = 0; i < num_tests; i++) {
        if (is_ending_with_alphanumeric(test_strings[i], max_len)) {
            printf("\"%s\" ends with alphanumeric characters.\n", test_strings[i]);
        } else {
            printf("\"%s\" does NOT end with only alphanumeric characters.\n", test_strings[i]);
        }
    }

    return 0;
}