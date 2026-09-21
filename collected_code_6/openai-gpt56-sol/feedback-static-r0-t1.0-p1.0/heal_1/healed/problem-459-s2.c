#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(char *string, size_t capacity)
{
    static const char pattern[] = "[[:upper:]]+";
    regex_t regex;
    regmatch_t match;
    size_t length;
    size_t read_offset = 0;
    size_t write_offset = 0;
    int status;

    if (string == NULL || capacity == 0) {
        return REG_BADPAT;
    }

    length = strnlen(string, capacity);
    if (length == capacity) {
        return REG_BADPAT;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
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

        if (status != 0) {
            regfree(&regex);
            return status;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > length - read_offset) {
            regfree(&regex);
            return REG_BADPAT;
        }

        {
            size_t prefix_length = (size_t)match.rm_so;
            size_t match_end = (size_t)match.rm_eo;

            memmove(string + write_offset, string + read_offset,
                    prefix_length);
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
    const char *input;
    char *string;
    size_t length;
    size_t capacity;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    if (input == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    length = strlen(input);
    if (length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    capacity = length + 1;
    string = malloc(capacity);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memmove(string, input, capacity);

    status = remove_uppercase_substrings(string, capacity);
    if (status != 0) {
        size_t error_length = regerror(status, NULL, NULL, 0);
        char *error_buffer;

        if (error_length == 0) {
            fputs("Regex error\n", stderr);
            free(string);
            return EXIT_FAILURE;
        }

        error_buffer = malloc(error_length);
        if (error_buffer == NULL) {
            fputs("Regex error and memory allocation failed\n", stderr);
            free(string);
            return EXIT_FAILURE;
        }

        regerror(status, NULL, error_buffer, error_length);
        fprintf(stderr, "Regex error: %s\n", error_buffer);
        free(error_buffer);
        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);
    return EXIT_SUCCESS;
}