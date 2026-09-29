#include <stdio.h>
#include <string.h>
#include <regex.h>

int match(const char *string) {
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "a.*b$", 0);
    if (ret) {
        return 0;
    }
    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    }
    return 0;
}

int main() {
    char *test1 = "abc";
    char *test2 = "acb";
    printf("%d\n", match(test1)); // should return 1
    printf("%d\n", match(test2)); // should return 0
    return 0;
}