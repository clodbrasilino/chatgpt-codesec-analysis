#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_string(const char *str) {
    regex_t regex;
    int reti;
    int result = 0;

    if (str == NULL) {
        return -1;
    }

    reti = regcomp(&regex, "^ab*$", REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    } else if (reti == REG_NOMATCH) {
        result = 0;
    } else {
        result = -1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abb",
        "abbb",
        "b",
        "ba",
        "abc",
        "aa",
        ""
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    int i;
    int match_result;

    for (i = 0; i < num_tests; i++) {
        match_result = match_string(test_strings[i]);
        if (match_result == 1) {
            printf("\"%s\": Match\n", test_strings[i]);
        } else if (match_result == 0) {
            printf("\"%s\": No match\n", test_strings[i]);
        } else {
            printf("\"%s\": Error\n", test_strings[i]);
        }
    }

    return 0;
}