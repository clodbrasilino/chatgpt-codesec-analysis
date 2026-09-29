#include <stdint.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_lowercase_substrings(const char *input, size_t input_length,
                                       char **output)
{
    regex_t regex;
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
                regfree(&regex);
                free(result);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + destination_offset,
                   input + source_offset,
                   remaining);
            destination_offset += remaining;
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
             */
            match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return -1;
        }

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if ((uintmax_t)match.rm_so > SIZE_MAX ||
            (uintmax_t)match.rm_eo > SIZE_MAX) {
            regfree(&regex);
            free(result);
            return -1;
        }

        /* Possible weaknesses found:
         *  prefix_length is assigned '(unsigned long)match.rm_so' here.
         */
        prefix_length = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'match_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=prefix_length
         */
        match_end = (size_t)match.rm_eo;

        /* Possible weaknesses found:
         *  Condition 'prefix_length>match_end' is always true [knownConditionTrueFalse]
         *  Condition 'prefix_length>match_end' is always true
         */
        if (prefix_length > match_end ||
            match_end > remaining ||
            prefix_length > input_length - destination_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        if (prefix_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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
}

int main(int argc, char *argv[])
{
    char *output = NULL;
    const char *program;
    size_t input_length;

    program = argc > 0 && argv != NULL && argv[0] != NULL
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);

    if (remove_lowercase_substrings(argv[1], input_length, &output) != 0) {
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