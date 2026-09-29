#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_string(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", 0);
    if (ret != 0) {
        return false;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main() {
    const char *test_strings[] = {"abc123", "abc!@#", "ABC123", "abc 123", "", "0123456789"};
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        printf("Is '%s' valid? %s\n", test_strings[i], is_valid_string(test_strings[i]) ? "Yes" : "No");
    }

    return 0;
}