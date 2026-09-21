#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int report_regex_error(int status, const regex_t *regex,
                              const char *operation)
{
    size_t required;
    char *buffer;

    required = regerror(status, regex, NULL, 0);
    if (required == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    buffer = malloc(required);
    if (buffer == NULL) {
        fprintf(stderr, "%s failed; unable to allocate error buffer\n",
                operation);
        return -1;
    }

    (void)regerror(status, regex, buffer, required);
    fprintf(stderr, "%s failed: %s\n", operation, buffer);
    free(buffer);

    return -1;
}

static int find_sequences(const char *input)
{
    regex_t regex;
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]][[:lower:]]+", REG_EXTENDED);
    if (status != 0) {
        return report_regex_error(status, NULL, "regcomp");
    }

    cursor = input;

    while (*cursor != '\0') {
        regmatch_t match;
        size_t offset;
        size_t length;

        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            (void)report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        offset = (size_t)match.rm_so;
        length = (size_t)(match.rm_eo - match.rm_so);

        if (fwrite(cursor + offset, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    size_t argument_count;
    size_t total_length = 0;
    size_t *lengths = NULL;
    char *input = NULL;
    char *destination;
    int result = EXIT_FAILURE;

    if (argc < 2 || argv == NULL) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <text>\n", program);
        return EXIT_FAILURE;
    }

    argument_count = (size_t)argc - 1U;

    if (argument_count > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    lengths = malloc(argument_count * sizeof(*lengths));
    if (lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < argument_count; ++i) {
        size_t length;

        if (argv[i + 1U] == NULL) {
            fprintf(stderr, "Invalid argument\n");
            goto cleanup;
        }

        length = strnlen(argv[i + 1U], SIZE_MAX);
        lengths[i] = length;

        if (length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            goto cleanup;
        }

        total_length += length;

        if (i + 1U < argument_count) {
            if (total_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                goto cleanup;
            }
            ++total_length;
        }
    }

    if (total_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        goto cleanup;
    }

    input = malloc(total_length + 1U);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    destination = input;

    for (size_t i = 0; i < argument_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, argv[i + 1U], lengths[i]);
        destination += lengths[i];

        if (i + 1U < argument_count) {
            *destination++ = ' ';
        }
    }

    *destination = '\0';

    if (find_sequences(input) != 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    free(lengths);
    return result;
}