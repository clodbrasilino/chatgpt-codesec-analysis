#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int starts_with_vowel(const char *str) {
    regex_t regex;
    int result;
    const char *pattern = "^[aeiouAEIOU]";
    
    if (str == NULL) {
        return 0;
    }
    
    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return 0;
    }
    
    result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    return (result == 0) ? 1 : 0;
}

int main(void) {
    const char *test_strings[] = {
        "apple",
        "banana",
        "Orange",
        "grape",
        "umbrella",
        "xyz",
        "",
        "Elephant"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        if (starts_with_vowel(test_strings[i])) {
            printf("\"%s\" starts with a vowel.\n", test_strings[i]);
        } else {
            printf("\"%s\" does not start with a vowel.\n", test_strings[i]);
        }
    }
    
    return 0;
}