#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_with_colons(const char *string, char **output)
{
    regex_t regex;
    regmatch_t match;
    char *copy;
    char *cursor;
    size_t length;
    int result;

    if (string == NULL || output == NULL) {
        return REG_BADPAT;
    }

    *output = NULL;

    result = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (result != 0) {
        return result;
    }

    length = strlen(string);
    copy = malloc(length + 1);
    if (copy == NULL) {
        regfree(&regex);
        return REG_ESPACE;
    }

    memcpy(copy, string, length + 1);
    cursor = copy;

    while ((result = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            free(copy);
            regfree(&regex);
            return REG_BADPAT;
        }

        cursor[(size_t)match.rm_so] = ':';
        cursor += (size_t)match.rm_eo;
    }

    regfree(&regex);

    if (result != REG_NOMATCH) {
        free(copy);
        return result;
    }

    *output = copy;
    return 0;
}

int main(int argc, char **argv)
{
    char *result_string;
    const char *program;
    int result;

    if (argc != 2) {
        program = argc > 0 && argv != NULL && argv[0] != NULL
                      ? argv[0]
                      : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    result = replace_with_colons(argv[1], &result_string);
    if (result != 0) {
        if (fputs("Regular expression processing failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(result_string) == EOF) {
        free(result_string);
        return EXIT_FAILURE;
    }

    free(result_string);
    return EXIT_SUCCESS;
}