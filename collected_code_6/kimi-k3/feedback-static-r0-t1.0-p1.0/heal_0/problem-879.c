#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_pattern(const char *string) {
    regex_t regex;
    int ret;
    int result = 0;
    
    if (string == NULL) {
        return 0;
    }
    
    ret = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, string, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    }
    
    regfree(&regex);
    
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "acb",
        "a123b",
        "a b",
        "ba",
        "abc",
        "cab",
        "a",
        "b",
        ""
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    int i;
    
    for (i = 0; i < num_tests; i++) {
        if (match_pattern(test_strings[i])) {
            printf("\"%s\": Match\n", test_strings[i]);
        } else {
            printf("\"%s\": No match\n", test_strings[i]);
        }
    }
    
    return 0;
}