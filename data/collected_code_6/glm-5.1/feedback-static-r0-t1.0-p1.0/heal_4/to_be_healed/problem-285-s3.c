#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int match_a_bbs(const char *string) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^abb[b]?$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) >= 5) {
        if (match_a_bbs(argv[1])) {
            printf("Match\n");
        } else {
            printf("No Match\n");
        }
    } else {
        printf("No Match\n");
    }

    return EXIT_SUCCESS;
}