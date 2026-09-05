#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int starts_with_vowel(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test1 = "apple";
    const char *test2 = "banana";
    const char *test3 = "Orange";
    const char *test4 = "";

    printf("%s: %d\n", test1, starts_with_vowel(test1));
    printf("%s: %d\n", test2, starts_with_vowel(test2));
    printf("%s: %d\n", test3, starts_with_vowel(test3));
    printf("%s: %d\n", test4, starts_with_vowel(test4));

    return 0;
}