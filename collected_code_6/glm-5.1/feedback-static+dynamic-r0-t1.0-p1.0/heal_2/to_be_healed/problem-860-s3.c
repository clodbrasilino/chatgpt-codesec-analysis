#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int ends_with_alphanumeric(const char *str, size_t maxlen) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, maxlen);
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
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (ends_with_alphanumeric(argv[1], 4096)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}