#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *current;
    size_t input_length;
    int status;
    int result = EXIT_FAILURE;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    if (input_length > (size_t)PTRDIFF_MAX) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    current = input;

    while (*current != '\0') {
        size_t remaining_length = input_length - (size_t)(current - input);

        status = regexec(&regex, current + 1, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (fwrite(current, 1, remaining_length, stdout) != remaining_length ||
                fputc('\n', stdout) == EOF) {
                goto cleanup;
            }
            result = EXIT_SUCCESS;
            goto cleanup;
        }

        if (status != 0 || match.rm_so < 0) {
            goto cleanup;
        }

        size_t segment_length = (size_t)match.rm_so + 1;

        if (segment_length > remaining_length) {
            goto cleanup;
        }

        if (fwrite(current, 1, segment_length, stdout) != segment_length ||
            fputc('\n', stdout) == EOF) {
            goto cleanup;
        }

        current += segment_length;
    }

    result = EXIT_SUCCESS;

cleanup:
    regfree(&regex);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}