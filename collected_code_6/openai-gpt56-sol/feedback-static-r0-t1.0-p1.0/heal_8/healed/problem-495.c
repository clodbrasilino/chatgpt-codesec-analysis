#include <stdint.h>
#include <inttypes.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_lowercase_substrings(const char *input, size_t input_length,
                                       char **output)
{
    regex_t regex;
    char *result = NULL;
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

    status = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return -1;
    }

    while (source_offset < input_length) {
        regmatch_t match;
        size_t remaining = input_length - source_offset;
        size_t prefix_length;
        size_t match_end;

        status = regexec(&regex, input + source_offset, 1, &match, 0);
        if (status == REG_NOMATCH) {
            if (remaining > input_length - destination_offset) {
                goto fail;
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

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0) {
            goto fail;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match.rm_eo > (uintmax_t)SIZE_MAX) {
            goto fail;
        }

        prefix_length = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_end <= prefix_length ||
            match_end > remaining ||
            prefix_length > input_length - destination_offset) {
            goto fail;
        }

        if (prefix_length != 0) {
            memcpy(result + destination_offset,
                   input + source_offset,
                   prefix_length);
            destination_offset += prefix_length;
        }

        source_offset += match_end;
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;
    return 0;

fail:
    regfree(&regex);
    free(result);
    return -1;
}

int main(int argc, char *argv[])
{
    char *output = NULL;
    const char *program;
    const char *input;
    size_t input_length;

    program = argc > 0 && argv != NULL && argv[0] != NULL
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = strlen(input);

    if (remove_lowercase_substrings(input, input_length, &output) != 0) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}