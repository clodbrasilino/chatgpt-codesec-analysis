#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int remove_uppercase_substrings(const char *input, size_t input_length,
                                char **output)
{
    regex_t regex;
    char *source;
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

    source = malloc(input_length + 1);
    if (source == NULL) {
        return REG_ESPACE;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        free(source);
        return REG_ESPACE;
    }

    if (input_length != 0) {
        memcpy(source, input, input_length);
    }
    source[input_length] = '\0';

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        free(source);
        return status;
    }

    while (read_offset < input_length) {
        regmatch_t match;
        size_t remaining = input_length - read_offset;
        size_t prefix_length;
        size_t match_end;

        status = regexec(&regex, source + read_offset, 1, &match, 0);
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

        if ((uintmax_t)match.rm_so > SIZE_MAX ||
            (uintmax_t)match.rm_eo > SIZE_MAX) {
            status = REG_ESPACE;
            break;
        }

        prefix_length = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_end > remaining ||
            write_offset > input_length ||
            prefix_length > input_length - write_offset) {
            status = REG_ESPACE;
            break;
        }

        if (prefix_length != 0) {
            memcpy(result + write_offset, source + read_offset,
                   prefix_length);
            write_offset += prefix_length;
        }

        read_offset += match_end;
    }

    if (status == 0) {
        size_t remaining = input_length - read_offset;

        if (write_offset > input_length ||
            remaining > input_length - write_offset) {
            status = REG_ESPACE;
        } else {
            if (remaining != 0) {
                memcpy(result + write_offset, source + read_offset,
                       remaining);
                write_offset += remaining;
            }
            result[write_offset] = '\0';
        }
    }

    regfree(&regex);
    free(source);

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

    if (input_length != 0 && input[input_length - 1] == '\n') {
        --input_length;
    }

    if (input_length != 0 && input[input_length - 1] == '\r') {
        --input_length;
    }

    status = remove_uppercase_substrings(input, input_length, &output);
    free(input);

    if (status != 0) {
        size_t message_length = regerror(status, NULL, NULL, 0);
        char *message = NULL;

        if (message_length != 0) {
            message = malloc(message_length);
        }

        if (message != NULL) {
            (void)regerror(status, NULL, message, message_length);
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