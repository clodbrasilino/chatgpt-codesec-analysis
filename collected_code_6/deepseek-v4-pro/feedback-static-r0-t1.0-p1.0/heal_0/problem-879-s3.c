#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int match_pattern(const char *str) {
    regex_t regex;
    int ret;
    const char *pattern = "^a.*b$";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "a123b",
        "acb",
        "aXYZb",
        "b",
        "a",
        "abc",
        "a b",
        "ba",
        "a\nb"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        int result = match_pattern(test_strings[i]);
        if (result == 1) {
            printf("'%s' matches\n", test_strings[i]);
        } else if (result == 0) {
            printf("'%s' does not match\n", test_strings[i]);
        } else {
            fprintf(stderr, "Error processing '%s'\n", test_strings[i]);
        }
    }
    
    return 0;
}