#include <stdio.h>
#include <string.h>
#include <regex.h>

int match_ab(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "a*b*", 0);
    if (ret) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    char *str = "abbbb";
    int result = match_ab(str);
    if (result == 1) {
        printf("Match found\n");
    } else if (result == 0) {
        printf("No match found\n");
    } else {
        printf("An error occurred\n");
    }
    return 0;
}