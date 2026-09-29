#include <errno.h>
#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alnum(const char *input, char **output)
{
    static const char pattern[] = "[^[:alnum:]]+";
    regex_t regex;
    regmatch_t match;
    char *result;
    char *destination;
    const char *cursor;
    size_t input_length;
    size_t consumed = 0;
    int status;

    if (output == NULL) {
        errno = EINVAL;
        return -1;
    }

    *output = NULL;

    if (input == NULL) {
        errno = EINVAL;
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        errno = status == REG_ESPACE ? ENOMEM : EINVAL;
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        regfree(&regex);
        errno = EOVERFLOW;
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        int saved_errno = errno;
        regfree(&regex);
        errno = saved_errno == 0 ? ENOMEM : saved_errno;
        return -1;
    }

    cursor = input;
    destination = result;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t match_start;
        size_t match_end;
        size_t remaining = input_length - consumed;

        if (match.rm_so < 0 ||
            match.rm_eo < match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            free(result);
            regfree(&regex);
            errno = EIO;
            return -1;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_end == 0) {
            free(result);
            regfree(&regex);
            errno = EIO;
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, cursor, match_start);
        destination += match_start;
        cursor += match_end;
        consumed += match_end;
    }

    if (status != REG_NOMATCH) {
        free(result);
        regfree(&regex);
        errno = status == REG_ESPACE ? ENOMEM : EIO;
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(destination, cursor, input_length - consumed);
    destination += input_length - consumed;
    *destination = '\0';

    regfree(&regex);
    *output = result;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *filtered;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <text>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (remove_non_alnum(argv[1], &filtered) != 0) {
        perror("remove_non_alnum");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", filtered) < 0) {
        free(filtered);
        return EXIT_FAILURE;
    }

    free(filtered);
    return EXIT_SUCCESS;
}