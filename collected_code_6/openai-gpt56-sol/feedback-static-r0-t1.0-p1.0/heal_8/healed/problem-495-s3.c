#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int remove_lowercase_substrings(const char *input, size_t input_length,
                                       char **output)
{
    static const char pattern[] = "[[:lower:]]+";
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

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(result);
        return -1;
    }

    while (source_offset < input_length) {
        size_t remaining = input_length - source_offset;
        size_t match_start;
        size_t match_end;

        status = regexec(&regex, input + source_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (remaining > input_length - destination_offset) {
                regfree(&regex);
                free(result);
                return -1;
            }

            memcpy(result + destination_offset,
                   input + source_offset,
                   remaining);
            destination_offset += remaining;
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return -1;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining || match_end > remaining ||
            match_start > input_length - destination_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        if (match_start > 0) {
            memcpy(result + destination_offset,
                   input + source_offset,
                   match_start);
            destination_offset += match_start;
        }

        source_offset += match_end;
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *result = NULL;
    size_t input_length;

    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                argv != NULL && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input_length = strlen(argv[1]);

    if (remove_lowercase_substrings(argv[1], input_length, &result) != 0) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}