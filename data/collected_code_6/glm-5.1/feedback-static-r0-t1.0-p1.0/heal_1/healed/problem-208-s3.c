#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int is_valid_decimal(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    const char *pattern = "^[+-]?([0-9]+\\.[0-9]{2}|[0-9]+)$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }

    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_decimal(argv[1])) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return EXIT_SUCCESS;
}