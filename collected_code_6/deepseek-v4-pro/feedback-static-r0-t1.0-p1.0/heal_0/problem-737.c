#include <stdio.h>
#include <regex.h>
#include <string.h>

int starts_with_vowel(const char *str) {
    regex_t regex;
    int ret;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "apple",
        "banana",
        "Orange",
        "grape",
        "Umbrella",
        "123abc",
        "",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("%s: %s\n", test_strings[i], 
               starts_with_vowel(test_strings[i]) ? "starts with vowel" : "does not start with vowel");
    }

    return 0;
}