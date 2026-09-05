#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int check_decimal_precision_2(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[+-]?[0-9]+(\\.[0-9]{1,2})?$", REG_EXTENDED);
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
        fprintf(stderr, "Usage: %s <decimal_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (check_decimal_precision_2(argv[1])) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return EXIT_SUCCESS;
}