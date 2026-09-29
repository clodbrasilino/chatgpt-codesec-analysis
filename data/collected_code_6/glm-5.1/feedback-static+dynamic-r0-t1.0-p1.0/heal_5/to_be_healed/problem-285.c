#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int match_a_two_three_b(const char *string) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^ab{2,3}$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) > 1024) {
        fprintf(stderr, "Input string exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    if (match_a_two_three_b(argv[1])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return EXIT_SUCCESS;
}