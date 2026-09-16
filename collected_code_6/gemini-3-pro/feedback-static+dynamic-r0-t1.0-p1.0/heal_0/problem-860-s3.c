#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int check_ends_with_alnum(const char *str) {
    regex_t regex;
    int comp_ret;
    int exec_ret;

    if (str == NULL) {
        return -1;
    }

    comp_ret = regcomp(&regex, "[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (comp_ret != 0) {
        return -1;
    }

    exec_ret = regexec(&regex, str, 0, NULL, 0);
    
    regfree(&regex);

    if (exec_ret == 0) {
        return 1;
    } else if (exec_ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(void) {
    const char *valid_str = "HelloWorld123";
    const char *invalid_str = "HelloWorld!!!";
    const char *empty_str = "";
    int result;

    result = check_ends_with_alnum(valid_str);
    if (result == 1) {
        printf("Valid\n");
    } else if (result == 0) {
        printf("Invalid\n");
    } else {
        printf("Error\n");
    }

    result = check_ends_with_alnum(invalid_str);
    if (result == 1) {
        printf("Valid\n");
    } else if (result == 0) {
        printf("Invalid\n");
    } else {
        printf("Error\n");
    }

    result = check_ends_with_alnum(empty_str);
    if (result == 1) {
        printf("Valid\n");
    } else if (result == 0) {
        printf("Invalid\n");
    } else {
        printf("Error\n");
    }

    return 0;
}