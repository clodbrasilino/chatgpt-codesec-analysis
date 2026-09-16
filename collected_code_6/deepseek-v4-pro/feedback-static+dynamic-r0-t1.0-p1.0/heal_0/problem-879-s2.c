#include <stdio.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *string) {
    regex_t regex;
    int ret;
    int match;
    
    ret = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    match = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    
    if (!match) {
        return 1;
    } else if (match == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "a123b",
        "aXYZb",
        "acb",
        "b",
        "a",
        "abc",
        "a b",
        "a\nb",
        "a\tb"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        if (match_pattern(test_strings[i])) {
            printf("'%s' matches\n", test_strings[i]);
        } else {
            printf("'%s' does not match\n", test_strings[i]);
        }
    }
    
    return 0;
}