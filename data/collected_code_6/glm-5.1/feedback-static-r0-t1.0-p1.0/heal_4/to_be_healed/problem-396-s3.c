#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int check_same_start_end(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    regex_t regex;
    int ret;
    char *pattern = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char escaped_char[5];

    if (str[0] == '\\') {
        snprintf(escaped_char, sizeof(escaped_char), "\\\\");
    } else if (strchr(".^$*+?()[{", str[0]) != NULL) {
        snprintf(escaped_char, sizeof(escaped_char), "\\%c", str[0]);
    } else {
        snprintf(escaped_char, sizeof(escaped_char), "%c", str[0]);
    }

    if (asprintf(&pattern, "^(%s).*\\1$", escaped_char) < 0) {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        free(pattern);
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    free(pattern);

    return ret == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (check_same_start_end(argv[1])) {
        printf("Match\n");
    } else {
        printf("No Match\n");
    }

    return EXIT_SUCCESS;
}