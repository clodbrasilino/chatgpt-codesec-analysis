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
    char *string = "abbbb";
    if (match(string)) {
        printf("Match\n");
    } else {
        printf("No Match\n");
    }
    return 0;
}