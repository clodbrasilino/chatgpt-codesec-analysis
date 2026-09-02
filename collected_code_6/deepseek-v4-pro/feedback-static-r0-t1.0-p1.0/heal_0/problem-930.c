#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *str) {
    regex_t regex;
    int ret;
    int match;

    ret = regcomp(&regex, "^ab*$", REG_EXTENDED);
    if (ret) {
        return 0;
    }

    match = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return (match == 0);
}

int main(int argc, char *argv[]) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abb",
        "abbb",
        "b",
        "ba",
        "abc",
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        if (match_pattern(test_strings[i])) {
            printf("Match: %s\n", test_strings[i]);
        } else {
            printf("No match: %s\n", test_strings[i]);
        }
    }

    if (argc > 1) {
        if (match_pattern(argv[1])) {
            printf("Match: %s\n", argv[1]);
        } else {
            printf("No match: %s\n", argv[1]);
        }
    }

    return 0;
}