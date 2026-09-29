#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_uppercase_substrings(const char *input, char **output)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    const char *cursor;
    size_t input_length;
    size_t write_offset = 0;
    int status;

    if (input == NULL || output == NULL) {
        return REG_BADPAT;
    }

    *output = NULL;
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return REG_ESPACE;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return REG_ESPACE;
    }

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return status;
    }

    cursor = input;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t prefix_length;

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return REG_BADPAT;
        }

        prefix_length = (size_t)match.rm_so;
        memcpy(result + write_offset, cursor, prefix_length);
        write_offset += prefix_length;
        cursor += (size_t)match.rm_eo;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        free(result);
        return status;
    }

    strcpy(result + write_offset, cursor);
    regfree(&regex);
    *output = result;

    return 0;
}

int main(void)
{
    char input[4096];
    char *output = NULL;
    int status;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Input is too long\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    status = remove_uppercase_substrings(input, &output);
    if (status != 0) {
        char message[256];

        regerror(status, NULL, message, sizeof message);
        fprintf(stderr, "Regex error: %s\n", message);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}