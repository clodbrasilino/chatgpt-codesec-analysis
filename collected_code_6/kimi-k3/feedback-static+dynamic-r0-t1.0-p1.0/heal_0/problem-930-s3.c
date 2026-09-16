#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int match_a_followed_by_b(const char *input) {
    regex_t regex;
    int ret;
    
    if (input == NULL) {
        return 0;
    }
    
    ret = regcomp(&regex, "^ab*$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    
    return (ret == 0) ? 1 : 0;
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
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        if (match_a_followed_by_b(test_strings[i])) {
            printf("\"%s\": Match\n", test_strings[i]);
        } else {
            printf("\"%s\": No match\n", test_strings[i]);
        }
    }
    
    return 0;
}