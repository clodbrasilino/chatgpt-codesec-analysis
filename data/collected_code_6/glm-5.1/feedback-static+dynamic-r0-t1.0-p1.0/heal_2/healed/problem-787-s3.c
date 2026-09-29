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

const char *safe_str(const char *str) {
    return str ? str : "(null)";
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "aabbb";
    const char *test3 = "abb";
    const char *test4 = NULL;
    const char *test5 = "abbbc";

    printf("%s: %d\n", safe_str(test1), match_abbb(test1));
    printf("%s: %d\n", safe_str(test2), match_abbb(test2));
    printf("%s: %d\n", safe_str(test3), match_abbb(test3));
    printf("%s: %d\n", safe_str(test4), match_abbb(test4));
    printf("%s: %d\n", safe_str(test5), match_abbb(test5));

    return 0;
}