#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input, size_t input_length,
                                       char **output)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t source_offset = 0;
    size_t destination_offset = 0;
    int status;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

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

            if (remaining != 0) {
                memcpy(result + destination_offset,
                       input + source_offset,
                       remaining);
                destination_offset += remaining;
            }

            source_offset = input_length;
            break;
        }

        if (status != 0 || match.rm_so < 0 ||
            match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > remaining || end > remaining ||
            start > input_length - destination_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        if (start != 0) {
            memcpy(result + destination_offset,
                   input + source_offset,
                   start);
            destination_offset += start;
        }

        if (end > input_length - source_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        source_offset += end;
    }

    if (destination_offset > input_length) {
        regfree(&regex);
        free(result);
        return -1;
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result = NULL;
    size_t input_length;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = strlen(input);

    if (input_length == SIZE_MAX ||
        remove_uppercase_substrings(input, input_length, &result) != 0) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}