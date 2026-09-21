#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input, char **output)
{
    static const char pattern[] = "[[:upper:]]+";
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_length;
    size_t source_offset = 0;
    size_t destination_offset = 0;
    int status;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(result);
        return -1;
    }

    while (source_offset < input_length) {
        size_t remaining = input_length - source_offset;
        size_t start;
        size_t end;

        status = regexec(&regex, input + source_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (remaining > input_length - destination_offset) {
                regfree(&regex);
                free(result);
                return -1;
            }

            memmove(result + destination_offset,
                    input + source_offset,
                    remaining);
            destination_offset += remaining;
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0) {
            regfree(&regex);
            free(result);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > end || end > remaining || start == end ||
            start > input_length - destination_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        if (start > 0) {
            memmove(result + destination_offset,
                    input + source_offset,
                    start);
            destination_offset += start;
        }

        source_offset += end;
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;

    return 0;
}

int main(int argc, char *argv[])
{
    char *result = NULL;
    const char *program;

    program = argc > 0 && argv != NULL && argv[0] != NULL
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    if (remove_uppercase_substrings(argv[1], &result) != 0) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}