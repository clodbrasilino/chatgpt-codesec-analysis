#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_whitespace_and_underscore(char *str)
{
    regex_t regex;
    regmatch_t match;
    int status;

    if (str == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:space:]_]", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    for (char *cursor = str; *cursor != '\0';) {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        char *matched = cursor + match.rm_so;
        *matched = (*matched == '_') ? ' ' : '_';
        cursor = matched + 1;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char * const argv[])
{
    char *text;
    size_t length;

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too long\n");
        return EXIT_FAILURE;
    }

    text = malloc(length + 1);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(text, argv[1], length + 1);

    if (replace_whitespace_and_underscore(text) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(text);
        return EXIT_FAILURE;
    }

    if (puts(text) == EOF) {
        fprintf(stderr, "Output failed\n");
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}