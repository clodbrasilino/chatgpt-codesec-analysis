#include <stdio.h>
#include <regex.h>
#include <string.h>

int check_string(char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[a-zA-Z0-9]*$", 0);
    if (ret) {
        printf("Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        printf("Regex match failed\n");
        return 0;
    }

    regfree(&regex);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if (check_string(str)) {
        printf("String is valid\n");
    } else {
        printf("String is not valid\n");
    }

    return 0;
}