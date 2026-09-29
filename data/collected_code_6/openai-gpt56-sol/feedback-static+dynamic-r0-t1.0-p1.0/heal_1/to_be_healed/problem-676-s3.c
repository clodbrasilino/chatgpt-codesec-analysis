#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alphanumeric(char *string)
{
    regex_t regex;
    regmatch_t match;
    char *source;
    char *destination;
    int status;

    if (string == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    source = string;
    destination = string;

    while ((status = regexec(&regex, source, 1, &match, 0)) == 0) {
        size_t prefix_length = (size_t)match.rm_so;

        memmove(destination, source, prefix_length);
        destination += prefix_length;
        source += (size_t)match.rm_eo;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(destination, source, strlen(source) + 1);
    regfree(&regex);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    if (remove_non_alphanumeric(input) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", input) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}