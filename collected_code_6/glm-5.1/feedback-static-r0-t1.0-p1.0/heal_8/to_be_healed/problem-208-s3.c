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

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    size_t max_len = sizeof(buffer) - 1;
    
    size_t len = strnlen(argv[1], max_len + 1);
    
    if (len > max_len) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, argv[1], len + 1);

    if (is_valid_decimal(buffer)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return EXIT_SUCCESS;
}