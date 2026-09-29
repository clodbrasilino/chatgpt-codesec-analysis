#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int check_string(const char *str) {
    regex_t regex;
    int ret;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *valid_str = "HelloWorld123";
    const char *invalid_str = "Hello_World!@#";

    if (check_string(valid_str)) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    if (check_string(invalid_str)) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    return EXIT_SUCCESS;
}