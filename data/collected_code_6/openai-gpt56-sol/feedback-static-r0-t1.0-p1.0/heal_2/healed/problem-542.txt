#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static int replace_delimiters(char *string)
{
    regex_t regex;
    regmatch_t match;
    char *cursor;
    int status;

    if (string == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    cursor = string;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so < 0) {
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match.rm_so;
        *cursor = ':';
        ++cursor;
    }

    regfree(&regex);
    return status == REG_NOMATCH ? 0 : -1;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *string;
    size_t length;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    length = strlen(input);

    if (length > SIZE_MAX - 1) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, input, length + 1);

    if (replace_delimiters(string) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}