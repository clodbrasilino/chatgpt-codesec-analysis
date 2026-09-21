#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int report_regex_error(int status, const regex_t *regex, const char *operation)
{
    size_t length = regerror(status, regex, NULL, 0);
    char *message = malloc(length);

    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    regerror(status, regex, message, length);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
    return -1;
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
        return report_regex_error(status, &regex, "regcomp");
    }

    cursor = input;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        {
            size_t offset = (size_t)match.rm_so;
            size_t length = (size_t)(match.rm_eo - match.rm_so);

            if (fwrite(cursor + offset, 1, length, stdout) != length ||
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    size_t total_length = 0;
    char *input;
    char *destination;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(argv[i]);
        size_t separator_length = (i + 1 < argc) ? 1U : 0U;

        if (length > SIZE_MAX - total_length ||
            separator_length > SIZE_MAX - total_length - length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += length + separator_length;
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
        size_t remaining = total_length - (size_t)(destination - input);
        int written = snprintf(destination, remaining + 1U, "%s%s",
                               argv[i], (i + 1 < argc) ? " " : "");

        if (written < 0 || (size_t)written > remaining) {
            fprintf(stderr, "Failed to construct input\n");
            free(input);
            return EXIT_FAILURE;
        }

        destination += (size_t)written;
    }

    if (find_sequences(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}