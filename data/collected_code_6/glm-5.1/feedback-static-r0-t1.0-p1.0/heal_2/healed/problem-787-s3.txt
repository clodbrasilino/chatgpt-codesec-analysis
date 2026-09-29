#include <stdio.h>
#include <string.h>
#include <regex.h>

int match_abbb(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^abbb$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "aabbb";
    const char *test3 = "abb";
    const char *test4 = "(null)";

    printf("%s: %d\n", test1, match_abbb(test1));
    printf("%s: %d\n", test2, match_abbb(test2));
    printf("%s: %d\n", test3, match_abbb(test3));
    printf("%s: %d\n", test4, match_abbb(strcmp(test4, "(null)") == 0 ? NULL : test4));

    return 0;
}