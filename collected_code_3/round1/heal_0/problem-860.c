#include <stdio.h>
#include <string.h>
#include <regex.h>

int check_alphanumeric(char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[a-zA-Z0-9]$", 0);
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
}

int main() {
    char str1[] = "HelloWorld123";
    char str2[] = "HelloWorld123!";
    
    if (check_alphanumeric(str1)) {
        printf("String ends with alphanumeric character\n");
    } else {
        printf("String does not end with alphanumeric character\n");
    }

    if (check_alphanumeric(str2)) {
        printf("String ends with alphanumeric character\n");
    } else {
        printf("String does not end with alphanumeric character\n");
    }

    return 0;
}