#include <stdio.h>
#include <regex.h>
#include <string.h>

int starts_ends_same(const char *str) {
    regex_t regex;
    int ret;
    char pattern[] = "^(.).*\\1$";

    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 256);
    if (len == 0 || len >= 256) {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[257] = {0};

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }

    if (len >= sizeof(input)) {
        input[sizeof(input) - 1] = '\0';
    }

    if (starts_ends_same(input)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }

    return 0;
}