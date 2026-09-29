#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int replace_with_colons(char *string)
{
    regex_t regex;
    regmatch_t match;
    char *cursor;
    int result;

    if (string == NULL) {
        return REG_BADPAT;
    }

    result = regcomp(&regex, "[ ,.]", REG_EXTENDED);
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

int main(int argc, char *argv[const])
{
    int result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    result = replace_with_colons(argv[1]);
    if (result != 0) {
        if (fputs("Regular expression processing failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}