#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(char *string)
{
    regex_t regex;
    regmatch_t match;
    size_t read_offset = 0;
    size_t write_offset = 0;
    int status;

    if (string == NULL) {
        return REG_BADPAT;
    }

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        return status;
    }

    while (string[read_offset] != '\0') {
        status = regexec(&regex, string + read_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            memmove(string + write_offset,
                    string + read_offset,
                    strlen(string + read_offset) + 1);
            regfree(&regex);
            return 0;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return status != 0 ? status : REG_BADPAT;
        }

        memmove(string + write_offset,
                string + read_offset,
                (size_t)match.rm_so);

        write_offset += (size_t)match.rm_so;
        read_offset += (size_t)match.rm_eo;
    }

    string[write_offset] = '\0';
    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *string;
    size_t length;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1);

    status = remove_uppercase_substrings(string);
    if (status != 0) {
        char error_buffer[256];

        regerror(status, NULL, error_buffer, sizeof error_buffer);
        fprintf(stderr, "Regex error: %s\n", error_buffer);
        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);
    return EXIT_SUCCESS;
}