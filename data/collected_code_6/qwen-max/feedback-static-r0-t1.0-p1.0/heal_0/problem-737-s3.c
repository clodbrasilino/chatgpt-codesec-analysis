#include <stdio.h>
#include <regex.h>

int starts_with_vowel(const char *str) {
    regex_t regex;
    int ret;

    if (regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED) != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);
    return (ret == 0) ? 1 : 0;
}

int main() {
    const char *test_string = "example";
    if (starts_with_vowel(test_string)) {
        printf("The string starts with a vowel.\n");
    } else {
        printf("The string does not start with a vowel.\n");
    }
    return 0;
}