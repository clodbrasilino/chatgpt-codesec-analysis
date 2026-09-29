#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *remaining;
    size_t remaining_length;
    int result = EXIT_FAILURE;
    int status;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining_length = strlen(input);
    remaining = malloc(remaining_length + 1);
    if (remaining == NULL) {
        regfree(&regex);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(remaining, input, remaining_length + 1);

    while (remaining_length != 0) {
        size_t split_index;

        status = regexec(&regex, remaining + 1, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (printf("%s\n", remaining) < 0) {
                goto cleanup;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0) {
            goto cleanup;
        }

        split_index = (size_t)match.rm_so + 1;
        if (split_index > remaining_length) {
            goto cleanup;
        }

        remaining[split_index] = '\0';

        if (printf("%s\n", remaining) < 0) {
            goto cleanup;
        }

        memmove(remaining,
                remaining + split_index,
                remaining_length - split_index + 1);
        remaining_length -= split_index;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(remaining);
    regfree(&regex);
    return result;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        (argc > 0 && argv != NULL && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}