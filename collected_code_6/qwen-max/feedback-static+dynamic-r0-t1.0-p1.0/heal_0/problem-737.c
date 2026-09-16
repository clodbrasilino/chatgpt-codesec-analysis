#include <stdio.h>
#include <regex.h>

int starts_with_vowel(const char *str) {
    int result;
    regex_t regex;
    const char *pattern = "^[aeiouAEIOU]";

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return -1;
    }

    if (regexec(&regex, str, 0, NULL, 0) == 0) {
        result = 1;
    } else {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *test_strings[] = {"apple", "banana", "orange", "umbrella", "elephant", "cherry"};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("%s: %s\n", test_strings[i], starts_with_vowel(test_strings[i]) ? "starts with vowel" : "does not start with vowel");
    }
    return 0;
}