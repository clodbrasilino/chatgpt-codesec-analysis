#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input, char **output)
{
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

    input_length = strnlen(input, SIZE_MAX);
    if (input_length == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return -1;
    }

    while (source_offset < input_length) {
        size_t available = input_length - source_offset;

        status = regexec(&regex, input + source_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (available > input_length - destination_offset) {
                regfree(&regex);
                free(result);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + destination_offset,
                   input + source_offset,
                   available);
            destination_offset += available;
            break;
        }

        if (status != 0 || match.rm_so < 0 ||
            match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return -1;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t end = (size_t)match.rm_eo;

            if (start > available || end > available ||
                start > input_length - destination_offset) {
                regfree(&regex);
                free(result);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + destination_offset,
                   input + source_offset,
                   start);

            destination_offset += start;
            source_offset += end;
        }
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;

    return 0;
}

int main(int argc, char *argv[])
{
    char *result = NULL;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL
                                  ? argv[0]
                                  : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    if (remove_uppercase_substrings(argv[1], &result) != 0) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}