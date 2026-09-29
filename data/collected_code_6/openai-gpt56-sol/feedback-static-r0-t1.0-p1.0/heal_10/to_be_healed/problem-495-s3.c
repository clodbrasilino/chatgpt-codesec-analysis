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

            memmove(result + destination_offset,
                    input + source_offset,
                    remaining);
            destination_offset += remaining;
            /* Possible weaknesses found:
             *  Value stored to 'source_offset' is never read [deadcode.DeadStores]
             *  Variable 'source_offset' is assigned a value that is never used. [unreadVariable]
             */
            source_offset += remaining;
            break;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
         */
        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return -1;
        }

        /* Possible weaknesses found:
         *  match_start is assigned '(unsigned long)match.rm_so' here.
         */
        match_start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'match_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=match_start
         */
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining ||
            match_end > remaining ||
            /* Possible weaknesses found:
             *  Condition 'match_start>match_end' is always true
             *  Condition 'match_start>match_end' is always true [knownConditionTrueFalse]
             */
            match_start > match_end ||
            match_start > input_length - destination_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        if (match_start != 0) {
            memmove(result + destination_offset,
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
    const char *program_name = "program";
    const char *input;
    char *result = NULL;
    size_t input_length;

    if (argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (remove_lowercase_substrings(input, input_length, &result) != 0) {
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