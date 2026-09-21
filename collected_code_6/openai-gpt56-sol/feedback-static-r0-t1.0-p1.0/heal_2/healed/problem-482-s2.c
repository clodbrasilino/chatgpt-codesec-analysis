#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void report_regex_error(const char *operation, int status,
                               const regex_t *regex)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message = malloc(size);

    if (message != NULL) {
        regerror(status, regex, message, size);
        fprintf(stderr, "%s failed: %s\n", operation, message);
        free(message);
    } else {
        fprintf(stderr, "%s failed\n", operation);
    }
}

static int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]][[:lower:]]+", REG_EXTENDED);
    if (status != 0) {
        report_regex_error("regcomp", status, &regex);
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error("regexec", status, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t length = (size_t)(match.rm_eo - match.rm_so);

            if (fwrite(cursor + start, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                perror("output");
                regfree(&regex);
                return -1;
            }
        }

        cursor += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    size_t total_length = 0;
    char *input;
    char *destination;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length;
        size_t separator = i + 1 < argc ? 1U : 0U;

        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid argument\n");
            return EXIT_FAILURE;
        }

        length = strlen(argv[i]);

        if (length > SIZE_MAX - total_length ||
            separator > SIZE_MAX - total_length - length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += length + separator;
    }

    if (total_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    input = malloc(total_length + 1U);
    if (input == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    destination = input;

    for (int i = 1; i < argc; ++i) {
        const char *source = argv[i];

        while (*source != '\0') {
            *destination++ = *source++;
        }

        if (i + 1 < argc) {
            *destination++ = ' ';
        }
    }

    *destination = '\0';

    if (find_sequences(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}