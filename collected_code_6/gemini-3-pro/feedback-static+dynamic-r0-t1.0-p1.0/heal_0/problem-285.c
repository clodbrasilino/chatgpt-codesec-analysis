#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int match_pattern(const char *str);

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int comp_ret;
    int exec_ret;
    int result = 0;

    comp_ret = regcomp(&regex, "ab{2,3}", REG_EXTENDED);
    if (comp_ret != 0) {
        return 0;
    }

    exec_ret = regexec(&regex, str, 0, NULL, 0);
    if (exec_ret == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "abb",
        "abbb",
        "abbbb",
        "cabbe",
        "a",
        "b",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        int is_match = match_pattern(test_strings[i]);
        printf("%s: %d\n", test_strings[i], is_match);
    }

    return EXIT_SUCCESS;
}