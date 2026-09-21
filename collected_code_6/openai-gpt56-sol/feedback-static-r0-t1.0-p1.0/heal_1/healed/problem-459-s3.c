#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_uppercase_substrings(const char *input, char **output)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t input_length;
    size_t remaining;
    size_t write_offset = 0;
    int status;

    if (input == NULL || output == NULL) {
        return REG_BADPAT;
    }

    *output = NULL;
    input_length = strlen(input);

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

    cursor = input;
    remaining = input_length;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t prefix_length;
        size_t match_end;

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(result);
            return REG_BADPAT;
        }

        prefix_length = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (prefix_length > remaining ||
            match_end > remaining ||
            write_offset > input_length - prefix_length) {
            regfree(&regex);
            free(result);
            return REG_ESPACE;
        }

        if (prefix_length != 0) {
            memcpy(result + write_offset, cursor, prefix_length);
            write_offset += prefix_length;
        }

        cursor += match_end;
        remaining -= match_end;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        free(result);
        return status;
    }

    if (write_offset > input_length - remaining) {
        regfree(&regex);
        free(result);
        return REG_ESPACE;
    }

    if (remaining != 0) {
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

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    status = remove_uppercase_substrings(input, &output);
    free(input);

    if (status != 0) {
        char *message;
        size_t message_length = regerror(status, NULL, NULL, 0);

        message = malloc(message_length);
        if (message != NULL) {
            regerror(status, NULL, message, message_length);
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