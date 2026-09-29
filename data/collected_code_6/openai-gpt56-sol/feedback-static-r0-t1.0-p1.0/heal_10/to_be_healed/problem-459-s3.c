#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int remove_uppercase_substrings(const char *input, size_t input_length,
                                char **output)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t read_offset = 0;
    size_t write_offset = 0;
    int status;

    if (input == NULL || output == NULL) {
        return REG_BADPAT;
    }

    *output = NULL;

    if (input_length == SIZE_MAX) {
        return REG_ESPACE;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return REG_ESPACE;
    }

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return status;
    }

    while (read_offset < input_length) {
        size_t remaining = input_length - read_offset;
        size_t prefix_length;
        size_t match_end;

        status = regexec(&regex, input + read_offset, 1, &match,
                         /* Possible weaknesses found:
                          *  'REG_STARTEND' undeclared (first use in this function); did you mean 'REG_EPAREN'?
                          *  use of undeclared identifier 'REG_STARTEND'
                          *  each undeclared identifier is reported only once for each function it appears in
                          */
                         REG_STARTEND);
        if (status == 0) {
            match.rm_so = 0;
            match.rm_eo = (regoff_t)remaining;
            status = regexec(&regex, input + read_offset, 1, &match,
                             /* Possible weaknesses found:
                              *  use of undeclared identifier 'REG_STARTEND'
                              */
                             REG_STARTEND);
        }

        if (status == REG_NOMATCH) {
            status = 0;
            break;
        }

        if (status != 0) {
            break;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            status = REG_BADPAT;
            break;
        }

        prefix_length = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (prefix_length > remaining || match_end > remaining ||
            prefix_length > input_length - write_offset) {
            status = REG_ESPACE;
            break;
        }

        for (size_t i = 0; i < prefix_length; ++i) {
            result[write_offset++] = input[read_offset + i];
        }

        read_offset += match_end;
    }

    if (status == 0) {
        size_t remaining = input_length - read_offset;

        if (remaining > input_length - write_offset) {
            status = REG_ESPACE;
        } else {
            for (size_t i = 0; i < remaining; ++i) {
                result[write_offset++] = input[read_offset + i];
            }
            result[write_offset] = '\0';
        }
    }

    regfree(&regex);

    if (status != 0) {
        free(result);
        return status;
    }

    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 0;
    size_t input_length;
    ssize_t length;
    int status;

    errno = 0;
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

    input_length = (size_t)length;

    if (input_length > 0 && input[input_length - 1] == '\n') {
        --input_length;
    }

    if (input_length > 0 && input[input_length - 1] == '\r') {
        --input_length;
    }

    status = remove_uppercase_substrings(input, input_length, &output);
    free(input);

    if (status != 0) {
        size_t message_length = regerror(status, NULL, NULL, 0);

        if (message_length > 0 && message_length != SIZE_MAX) {
            char *message = malloc(message_length);

            if (message != NULL) {
                regerror(status, NULL, message, message_length);
                fprintf(stderr, "Regex error: %s\n", message);
                free(message);
                return EXIT_FAILURE;
            }
        }

        fprintf(stderr, "Regex error: %d\n", status);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}