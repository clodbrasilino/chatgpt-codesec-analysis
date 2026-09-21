#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_uppercase_substrings(const char *input, size_t input_length,
                                char **output)
{
    static const char pattern[] = "[[:upper:]]+";
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

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(result);
        return status;
    }

    while (read_offset < input_length) {
        size_t remaining = input_length - read_offset;
        size_t start;
        size_t end;

        status = regexec(&regex, input + read_offset, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            goto failure;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            status = REG_BADPAT;
            goto failure;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > remaining || end > remaining) {
            status = REG_BADPAT;
            goto failure;
        }

        if (start > input_length - write_offset) {
            status = REG_ESPACE;
            goto failure;
        }

        for (size_t i = 0; i < start; ++i) {
            result[write_offset++] = input[read_offset + i];
        }

        read_offset += end;
    }

    if (read_offset > input_length) {
        status = REG_BADPAT;
        goto failure;
    }

    while (read_offset < input_length) {
        if (write_offset >= input_length) {
            status = REG_ESPACE;
            goto failure;
        }

        result[write_offset++] = input[read_offset++];
    }

    result[write_offset] = '\0';

    regfree(&regex);
    *output = result;
    return 0;

failure:
    regfree(&regex);
    free(result);
    return status;
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
        input[--input_length] = '\0';
    }

    if (input_length > 0 && input[input_length - 1] == '\r') {
        input[--input_length] = '\0';
    }

    status = remove_uppercase_substrings(input, input_length, &output);
    free(input);

    if (status != 0) {
        size_t message_size = regerror(status, NULL, NULL, 0);
        char *message = NULL;

        if (message_size > 0) {
            message = malloc(message_size);
        }

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