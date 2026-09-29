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

    return ret == 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t max_len = 1023;
    size_t len = strnlen(argv[1], max_len + 1);
    
    if (len > max_len) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, argv[1], len + 1);

    if (is_valid_decimal(buffer)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    free(buffer);

    return EXIT_SUCCESS;
}