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

    remaining_length = strlen(input);
    remaining = malloc(remaining_length + 1);
    if (remaining == NULL) {
        regfree(&regex);
        return EXIT_FAILURE;
    }

    memcpy(remaining, input, remaining_length + 1);

    while (remaining_length > 0) {
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

        size_t split_index = (size_t)match.rm_so + 1;

        if (split_index > remaining_length) {
            goto cleanup;
        }

        char saved = remaining[split_index];
        remaining[split_index] = '\0';

        if (printf("%s\n", remaining) < 0) {
            remaining[split_index] = saved;
            goto cleanup;
        }

        remaining[split_index] = saved;
        remaining_length -= split_index;
        memmove(remaining, remaining + split_index, remaining_length + 1);
    }

    result = EXIT_SUCCESS;

cleanup:
    free(remaining);
    regfree(&regex);
    return result;
}

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