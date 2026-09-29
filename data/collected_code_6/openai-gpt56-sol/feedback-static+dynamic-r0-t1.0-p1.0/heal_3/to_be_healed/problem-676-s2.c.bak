#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_non_alphanumeric(char *string)
{
    regex_t regex;
    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    while (string[read_pos] != '\0') {
        result = regexec(&regex, string + read_pos, 1, &match, 0);

        if (result == REG_NOMATCH) {
            size_t remaining = strlen(string + read_pos);
            memmove(string + write_pos, string + read_pos, remaining + 1);
            regfree(&regex);
            return 0;
        }

        if (result != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        {
            size_t keep_length = (size_t)match.rm_so;
            size_t match_end = (size_t)match.rm_eo;

            memmove(string + write_pos, string + read_pos, keep_length);
            write_pos += keep_length;
            read_pos += match_end;
        }
    }

    string[write_pos] = '\0';
    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *string;
    size_t length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1);

    if (remove_non_alphanumeric(string) != 0) {
        fprintf(stderr, "Failed to process string\n");
        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);
    return EXIT_SUCCESS;
}