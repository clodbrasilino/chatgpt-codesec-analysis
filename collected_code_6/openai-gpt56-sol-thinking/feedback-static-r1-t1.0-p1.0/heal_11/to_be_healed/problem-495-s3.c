#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t size;
    char *message;

    size = regerror(error_code, regex, NULL, 0);
    if (size == 0) {
        fputs("Regular expression error\n", stderr);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fputs("Regular expression error\n", stderr);
        return;
    }

    regerror(error_code, regex, message, size);
    fprintf(stderr, "Regular expression error: %s\n", message);
    free(message);
}

static int remove_lowercase_substrings(char *string)
{
    regex_t regex;
    char *read_cursor;
    char *write_cursor;
    size_t remaining;
    int result;

    if (string == NULL) {
        fputs("Invalid string\n", stderr);
        return -1;
    }

    result = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    read_cursor = string;
    write_cursor = string;
    remaining = strlen(string);

    for (;;) {
        regmatch_t match;
        size_t start;
        size_t end;

        result = regexec(&regex, read_cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            memmove(write_cursor, read_cursor, remaining + 1);
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fputs("Invalid regular expression match\n", stderr);
            regfree(&regex);
            return -1;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match.rm_eo > (uintmax_t)SIZE_MAX) {
            fputs("Regular expression match is too large\n", stderr);
            regfree(&regex);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (end > remaining) {
            fputs("Regular expression match exceeds string bounds\n", stderr);
            regfree(&regex);
            return -1;
        }

        memmove(write_cursor, read_cursor, start);
        write_cursor += start;
        read_cursor += end;
        remaining -= end;
    }

    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    const char *input;
    char *string;
    size_t length;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    if (input == NULL) {
        fputs("Invalid input string\n", stderr);
        return EXIT_FAILURE;
    }

    length = strlen(input);
    if (length == SIZE_MAX) {
        fputs("Input string is too large\n", stderr);
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(string, input, length + 1);
    status = EXIT_FAILURE;

    if (remove_lowercase_substrings(string) == 0) {
        if (printf("%s\n", string) < 0) {
            fputs("Output error\n", stderr);
        } else {
            status = EXIT_SUCCESS;
        }
    }

    free(string);
    return status;
}