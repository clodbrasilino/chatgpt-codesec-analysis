#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int starts_with_vowel(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    int result = 0;

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

int main() {
    const char *test_strings[] = {
        "Apple",
        "banana",
        "Elephant",
        "igloo",
        "Octopus",
        "umbrella",
        "xylophone",
        "123",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        if (starts_with_vowel(test_strings[i])) {
            printf("\"%s\" starts with a vowel.\n", test_strings[i]);
        } else {
            printf("\"%s\" does not start with a vowel.\n", test_strings[i]);
        }
    }

    return 0;
}