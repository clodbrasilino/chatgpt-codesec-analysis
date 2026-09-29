#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_with_colons(char *string)
{
    regex_t regex;
    regmatch_t match;
    char *cursor;
    int result;

    if (string == NULL) {
        return REG_BADPAT;
    }

    result = regcomp(&regex, "[ ,\\.]", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    cursor = string;

    while ((result = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        cursor[match.rm_so] = ':';
        cursor += match.rm_eo;
    }

    regfree(&regex);

    return result == REG_NOMATCH ? 0 : result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *string;
    size_t length;
    int result;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(argv[1]);
    string = malloc(length + 1);
    if (string == NULL) {
        if (fputs("Memory allocation failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, argv[1], length + 1);

    result = replace_with_colons(string);
    if (result != 0) {
        free(string);
        if (fputs("Regular expression processing failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}