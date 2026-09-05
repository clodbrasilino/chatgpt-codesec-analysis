#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int starts_ends_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    regex_t regex;
    int ret = regcomp(&regex, "^(.).*\\1$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(void) {
    const char *test1 = "level";
    const char *test2 = "test";
    const char *test3 = "a";
    const char *test4 = "";

    printf("%s: %d\n", test1, starts_ends_same(test1));
    printf("%s: %d\n", test2, starts_ends_same(test2));
    printf("%s: %d\n", test3, starts_ends_same(test3));
    printf("%s: %d\n", test4, starts_ends_same(test4));

    return 0;
}