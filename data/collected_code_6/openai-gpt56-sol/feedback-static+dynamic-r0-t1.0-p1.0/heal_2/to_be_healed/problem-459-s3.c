#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_uppercase_substrings(const char *input, char **output)
{
    static const char pattern[] = "[[:upper:]]+";
    regex_t regex;
    regmatch_t match;
    char *result;
    const char *cursor;
    size_t input_length;
    size_t remaining;
    size_t write_offset = 0;
    int status;

    if (input == NULL || output == NULL) {
        return REG_BADPAT;
    }

    *output = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return REG_ESPACE;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return REG_ESPACE;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(result);
        return status;
    }

    cursor = input;
    remaining = input_length;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t start;
        size_t end;

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return REG_BADPAT;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > remaining || end > remaining ||
            write_offset > input_length ||
            start > input_length - write_offset) {
            regfree(&regex);
            free(result);
            return REG_ESPACE;
        }

        if (start != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + write_offset, cursor, start);
            write_offset += start;
        }

        cursor += end;
        remaining -= end;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        free(result);
        return status;
    }

    if (write_offset > input_length ||
        remaining > input_length - write_offset) {
        regfree(&regex);
        free(result);
        return REG_ESPACE;
    }

    if (remaining != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + write_offset, cursor, remaining);
        write_offset += remaining;
    }
    result[write_offset] = '\0';

    regfree(&regex);
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 0;
    ssize_t length;
    int status;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            perror("getline");
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_SUCCESS;
    }

    if (length > 0 && input[(size_t)length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[(size_t)length - 1] == '\r') {
        input[--length] = '\0';
    }

    status = remove_uppercase_substrings(input, &output);
    free(input);

    if (status != 0) {
        size_t message_size = regerror(status, NULL, NULL, 0);
        char *message = malloc(message_size);

        if (message != NULL) {
            regerror(status, NULL, message, message_size);
            fprintf(stderr, "Regex error: %s\n", message);
            free(message);
        } else {
            fprintf(stderr, "Regex error: %d\n", status);
        }

        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}