#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(char *string)
{
    regex_t regex;
    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, "  +", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    while ((result = regexec(&regex, string + read_pos, 1, &match, 0)) == 0) {
        size_t prefix_length = (size_t)match.rm_so;

        memmove(string + write_pos, string + read_pos, prefix_length);
        write_pos += prefix_length;
        string[write_pos++] = ' ';
        read_pos += (size_t)match.rm_eo;
    }

    if (result != REG_NOMATCH) {
        regfree(&regex);
        return -1;
    }

    memmove(string + write_pos, string + read_pos,
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strlen(string + read_pos) + 1);

    regfree(&regex);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];

    if (fgets(string, sizeof(string), stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(string, '\n') == NULL && !feof(stdin)) {
        int character;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    string[strcspn(string, "\n")] = '\0';

    if (remove_multiple_spaces(string) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}