#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int ends_with_alphanumeric(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-zA-Z0-9]$", REG_EXTENDED);
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (ends_with_alphanumeric(argv[1])) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}