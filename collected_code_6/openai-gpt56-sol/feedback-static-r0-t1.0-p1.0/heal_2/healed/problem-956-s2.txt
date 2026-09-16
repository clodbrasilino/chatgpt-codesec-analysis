#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *remaining;
    int result = EXIT_FAILURE;
    int status;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    remaining = strdup(input);
    if (remaining == NULL) {
        regfree(&regex);
        return EXIT_FAILURE;
    }

    while (remaining[0] != '\0') {
        size_t split_index;
        char saved;

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
        saved = remaining[split_index];
        remaining[split_index] = '\0';

        if (printf("%s\n", remaining) < 0) {
            remaining[split_index] = saved;
            goto cleanup;
        }

        remaining[split_index] = saved;
        memmove(remaining, remaining + split_index,
                strlen(remaining + split_index) + 1);
    }

    result = EXIT_SUCCESS;

cleanup:
    free(remaining);
    regfree(&regex);
    return result;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}