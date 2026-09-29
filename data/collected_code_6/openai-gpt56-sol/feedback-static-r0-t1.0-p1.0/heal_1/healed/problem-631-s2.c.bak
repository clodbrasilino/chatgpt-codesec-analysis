#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_whitespace_and_underscores(char *string)
{
    regex_t regex;
    regmatch_t match;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[[:space:]_]", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    for (size_t offset = 0; string[offset] != '\0';) {
        result = regexec(&regex, string + offset, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        size_t position = offset + (size_t)match.rm_so;
        string[position] = string[position] == '_' ? ' ' : '_';
        offset = position + 1;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char * const argv[])
{
    char *string;
    size_t length;

    if (argc != 2 || argv[0] == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too long\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1);

    if (replace_whitespace_and_underscores(string) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        fprintf(stderr, "Output failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}