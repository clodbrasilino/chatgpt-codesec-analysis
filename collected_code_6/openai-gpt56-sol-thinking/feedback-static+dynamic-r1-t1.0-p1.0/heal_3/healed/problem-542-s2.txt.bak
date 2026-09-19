#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int replace_with_colons(char *string)
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
    const char *input;
    char *string;
    size_t length;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = argv[1];
    length = strlen(input);

    string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(string, input, length + 1);

    result = replace_with_colons(string);
    if (result != 0) {
        fputs("Regular expression processing failed\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}