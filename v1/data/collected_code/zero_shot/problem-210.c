#include <stdio.h>
#include <regex.h>

int checkString(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
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

int main() {
    const char *str1 = "hello123";
    const char *str2 = "12@#$%^";
    
    if (checkString(str1)) {
        printf("String contains only the given set of characters.\n");
    } else {
        printf("String does not contain only the given set of characters.\n");
    }

    if (checkString(str2)) {
        printf("String contains only the given set of characters.\n");
    } else {
        printf("String does not contain only the given set of characters.\n");
    }

    return 0;
}