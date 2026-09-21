#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(char *string, size_t length)
{
    regex_t regex;
    regmatch_t match;
    size_t read_offset = 0;
    size_t write_offset = 0;
    int status;

    if (string == NULL || string[length] != '\0') {
        return REG_BADPAT;
    }

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        return status;
    }

    while (read_offset < length) {
        status = regexec(&regex, string + read_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            size_t remaining = length - read_offset;
            memmove(string + write_offset, string + read_offset, remaining);
            write_offset += remaining;
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > length - read_offset) {
            regfree(&regex);
            return status != 0 ? status : REG_BADPAT;
        }

        {
            size_t prefix_length = (size_t)match.rm_so;
            size_t match_end = (size_t)match.rm_eo;

            memmove(string + write_offset, string + read_offset, prefix_length);
            write_offset += prefix_length;
            read_offset += match_end;
        }
    }

    string[write_offset] = '\0';
    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    char *string;
    size_t length;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    length = strnlen(argv[1], (size_t)-1);
    if (length == (size_t)-1) {
        fputs("Input string is too long\n", stderr);
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memmove(string, argv[1], length);
    string[length] = '\0';

    status = remove_uppercase_substrings(string, length);
    if (status != 0) {
        size_t error_length = regerror(status, NULL, NULL, 0);
        char *error_buffer = malloc(error_length);

        if (error_buffer != NULL) {
            regerror(status, NULL, error_buffer, error_length);
            fprintf(stderr, "Regex error: %s\n", error_buffer);
            free(error_buffer);
        } else {
            fprintf(stderr, "Regex error code: %d\n", status);
        }

        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);
    return EXIT_SUCCESS;
}