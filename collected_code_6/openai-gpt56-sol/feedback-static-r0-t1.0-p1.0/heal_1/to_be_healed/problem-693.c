#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_multiple_spaces(char *string)
{
    regex_t regex;
    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;
    int status;

    if (string == NULL) {
        return -1;
    }

    status = regcomp(&regex, " {2,}", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while (string[read_pos] != '\0') {
        status = regexec(&regex, string + read_pos, 1, &match, 0);

        if (status == REG_NOMATCH) {
            memmove(string + write_pos,
                    string + read_pos,
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    strlen(string + read_pos) + 1);
            regfree(&regex);
            return 0;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        {
            size_t prefix_length = (size_t)match.rm_so;
            size_t match_length = (size_t)(match.rm_eo - match.rm_so);

            memmove(string + write_pos, string + read_pos, prefix_length);
            write_pos += prefix_length;
            string[write_pos++] = ' ';
            read_pos += prefix_length + match_length;
        }
    }

    string[write_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    input[strcspn(input, "\n")] = '\0';

    if (remove_multiple_spaces(input) != 0) {
        fprintf(stderr, "Failed to process input.\n");
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}