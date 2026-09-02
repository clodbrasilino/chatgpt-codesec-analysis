#include <stdio.h>
#include <regex.h>

int starts_with_vowel(const char *str) {
    regex_t regex;
    int ret;
    const char *pattern = "^[aeiouAEIOU]";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(void) {
    const char *test_strings[] = {
        "apple",
        "banana",
        "Orange",
        "grape",
        "umbrella",
        "pear",
        "Elephant",
        "123abc",
        "",
        "ice cream"
    };
    
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int result = starts_with_vowel(test_strings[i]);
        if (result == 1) {
            printf("'%s' starts with a vowel\n", test_strings[i]);
        } else if (result == 0) {
            printf("'%s' does not start with a vowel\n", test_strings[i]);
        } else {
            printf("Error processing '%s'\n", test_strings[i]);
        }
    }
    
    return 0;
}