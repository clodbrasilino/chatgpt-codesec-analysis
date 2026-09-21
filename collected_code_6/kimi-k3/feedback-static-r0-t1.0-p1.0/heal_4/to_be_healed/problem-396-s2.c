#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int starts_ends_same_char(const char *str) {
    regex_t regex;
    int reti;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    reti = regcomp(&regex, "^(.).*\\1$|^.$", REG_EXTENDED);
    if (reti != 0) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1025];
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[sizeof(input) - 1] = '\0';
    len = strnlen(input, sizeof(input));

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            ;
        }
    }

    if (starts_ends_same_char(input)) {
        printf("String starts and ends with the same character.\n");
    } else {
        printf("String does not start and end with the same character.\n");
    }

    return 0;
}