#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_non_alphanumeric(const char *input, size_t input_length)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    size_t read_position = 0;
    size_t write_position = 0;
    int status;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (status != 0) {
        free(output);
        return NULL;
    }

    while (read_position < input_length) {
        size_t remaining = input_length - read_position;
        char *segment = malloc(remaining + 1);

        if (segment == NULL) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(segment, input + read_position, remaining);
        segment[remaining] = '\0';

        status = regexec(&regex, segment, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (remaining > input_length - write_position) {
                free(segment);
                regfree(&regex);
                free(output);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + write_position, segment, remaining);
            write_position += remaining;
            free(segment);
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining) {
            free(segment);
            regfree(&regex);
            free(output);
            return NULL;
        }

        {
            size_t prefix_length = (size_t)match.rm_so;

            if (prefix_length > input_length - write_position) {
                free(segment);
                regfree(&regex);
                free(output);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + write_position, segment, prefix_length);
            write_position += prefix_length;
            read_position += (size_t)match.rm_eo;
        }

        free(segment);
    }

    output[write_position] = '\0';
    regfree(&regex);
    return output;
}

int main(void)
{
    static const char input[] = "Hello, World! 123_+-";
    char *result = remove_non_alphanumeric(input, sizeof(input) - 1);

    if (result == NULL) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}