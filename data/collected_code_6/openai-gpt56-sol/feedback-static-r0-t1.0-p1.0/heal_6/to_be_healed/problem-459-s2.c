#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

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
    if (length >= capacity) {
        return REG_BADPAT;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return status;
    }

    while (read_offset < length) {
        size_t remaining = length - read_offset;

        status = regexec(&regex, string + read_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (remaining > capacity - write_offset - 1) {
                regfree(&regex);
                return REG_ESPACE;
            }

            memmove(string + write_offset, string + read_offset, remaining);
            write_offset += remaining;
            break;
        }

        if (status != 0) {
            regfree(&regex);
            return status;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining) {
            regfree(&regex);
            return REG_BADPAT;
        }

        {
            size_t prefix_length = (size_t)match.rm_so;
            size_t match_end = (size_t)match.rm_eo;

            if (prefix_length > capacity - write_offset - 1) {
                regfree(&regex);
                return REG_ESPACE;
            }

            memmove(string + write_offset,
                    string + read_offset,
                    prefix_length);

            write_offset += prefix_length;
            read_offset += match_end;
        }
    }

    string[write_offset] = '\0';
    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *input;
    char *string;
    size_t length;
    size_t capacity;
    int status;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, input, length);
    string[length] = '\0';

    status = remove_uppercase_substrings(string, capacity);
    if (status != 0) {
        size_t error_length = regerror(status, NULL, NULL, 0);

        if (error_length > 0) {
            char *error_buffer = malloc(error_length);

            if (error_buffer != NULL) {
                regerror(status, NULL, error_buffer, error_length);
                fprintf(stderr, "Regex error: %s\n", error_buffer);
                free(error_buffer);
            } else {
                fputs("Regex error and memory allocation failed\n", stderr);
            }
        } else {
            fputs("Regex error\n", stderr);
        }

        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);
    return EXIT_SUCCESS;
}