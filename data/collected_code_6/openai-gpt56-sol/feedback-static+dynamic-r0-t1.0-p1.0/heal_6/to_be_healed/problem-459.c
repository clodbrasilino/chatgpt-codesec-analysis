#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input, char **output)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    const char *current;
    size_t input_length;
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

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return -1;
    }

    current = input;

    for (;;) {
        size_t prefix_length;

        status = regexec(&regex, current, 1, &match, 0);

        if (status == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(current);

            if (remaining > input_length - destination_offset) {
                regfree(&regex);
                free(result);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + destination_offset, current, remaining);
            destination_offset += remaining;
            break;
        }

        if (status != 0 || match.rm_so < 0 ||
            match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return -1;
        }

        prefix_length = (size_t)match.rm_so;

        if (prefix_length > input_length - destination_offset) {
            regfree(&regex);
            free(result);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + destination_offset, current, prefix_length);
        destination_offset += prefix_length;
        current += (size_t)match.rm_eo;
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;
    char *result = NULL;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        program_name = argc > 0 && argv != NULL && argv[0] != NULL
                           ? argv[0]
                           : "program";
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_uppercase_substrings(argv[1], &result) != 0) {
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