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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[static restrict argc]) {
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