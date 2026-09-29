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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(string + read_offset) + 1;
            memmove(string + write_offset, string + read_offset, remaining);
            regfree(&regex);
            return 0;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *string;
    size_t length;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(argv[1]);
    string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, argv[1], length + 1);

    status = remove_uppercase_substrings(string);
    if (status != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[256];

        regerror(status, NULL, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex error: %s\n", error_buffer);
        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);
    return EXIT_SUCCESS;
}