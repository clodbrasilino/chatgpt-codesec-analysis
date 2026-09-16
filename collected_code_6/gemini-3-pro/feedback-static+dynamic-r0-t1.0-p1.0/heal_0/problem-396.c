#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int check_start_end_same(const char *str) {
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }

    regex_t regex;
    int reti;
    const char *pattern = "^(.).*\\1$|^.$";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test_strings[] = {
        "radar",
        "hello",
        "a",
        "aa",
        "abc",
        "abca",
        "",
        NULL
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        if (test_strings[i] != NULL) {
            int result = check_start_end_same(test_strings[i]);
            printf("String: '%s' -> %s\n", test_strings[i], result ? "Match" : "No Match");
        }
    }

    return 0;
}