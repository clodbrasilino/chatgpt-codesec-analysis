#include <stdio.h>
#include <regex.h>

int match(const char *string) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "a*b*", 0);
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main() {
    printf("%d\n", match("abbb"));
    printf("%d\n", match("aaa"));
    printf("%d\n", match("bbb"));
    printf("%d\n", match("abc"));
    return 0;
}