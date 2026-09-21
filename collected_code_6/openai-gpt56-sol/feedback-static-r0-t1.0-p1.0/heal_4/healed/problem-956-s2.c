#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>
#include <stddef.h>

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    size_t input_length;
    size_t offset = 0;
    int status;
    int result = EXIT_FAILURE;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    input_length = strnlen(input, (size_t)PTRDIFF_MAX);
    if (input_length == (size_t)PTRDIFF_MAX) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    while (offset < input_length) {
        size_t remaining_length = input_length - offset;
        const char *search_start = input + offset + 1;

        status = regexec(&regex, search_start, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (fwrite(input + offset, 1, remaining_length, stdout) !=
                    remaining_length ||
                fputc('\n', stdout) == EOF) {
                goto cleanup;
            }

            result = EXIT_SUCCESS;
            goto cleanup;
        }

        if (status != 0 || match.rm_so < 0) {
            goto cleanup;
        }

        if ((uintmax_t)match.rm_so >= (uintmax_t)remaining_length) {
            goto cleanup;
        }

        {
            size_t segment_length = (size_t)match.rm_so + 1;

            if (fwrite(input + offset, 1, segment_length, stdout) !=
                    segment_length ||
                fputc('\n', stdout) == EOF) {
                goto cleanup;
            }

            offset += segment_length;
        }
    }

    result = EXIT_SUCCESS;

cleanup:
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
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}