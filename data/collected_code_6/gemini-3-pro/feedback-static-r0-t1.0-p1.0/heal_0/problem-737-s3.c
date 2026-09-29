#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        "apple",
        "Banana",
        "Elephant",
        "igloo",
        "Octopus",
        "umbrella",
        "sky",
        "123",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            int is_vowel = starts_with_vowel(test_strings[i]);
            printf("'%s' starts with vowel: %s\n", test_strings[i], is_vowel ? "Yes" : "No");
        }
    }

    return 0;
}