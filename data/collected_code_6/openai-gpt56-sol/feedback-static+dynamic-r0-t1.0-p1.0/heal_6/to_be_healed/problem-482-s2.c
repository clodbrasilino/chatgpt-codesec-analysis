#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int report_regex_error(int status, const regex_t *regex,
                              const char *operation)
{
    size_t length = regerror(status, regex, NULL, 0);
    char *message;

    if (length == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    message = malloc(length);
    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    (void)regerror(status, regex, message, length);
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
        return report_regex_error(status, NULL, "regcomp");
    }

    cursor = input;

    while (*cursor != '\0') {
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
            perror("output");
            regfree(&regex);
            return -1;
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
    size_t argument_count;
    size_t total_length = 0;
    size_t *lengths = NULL;
    char *input = NULL;
    char *destination;

    if (argc < 2 || argv == NULL) {
        fprintf(stderr, "Usage: %s <text>\n",
                argv != NULL && argc > 0 && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    argument_count = (size_t)argc - 1U;

    if (argument_count > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    lengths = malloc(argument_count * sizeof(*lengths));
    if (lengths == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < argument_count; ++i) {
        const char *argument = argv[i + 1U];
        size_t length;

        if (argument == NULL) {
            fprintf(stderr, "Invalid argument\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(argument);
        lengths[i] = length;

        if (length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        total_length += length;

        if (i + 1U < argument_count) {
            if (total_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                free(lengths);
                return EXIT_FAILURE;
            }

            ++total_length;
        }
    }

    if (total_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    input = malloc(total_length + 1U);
    if (input == NULL) {
        perror("malloc");
        free(lengths);
        return EXIT_FAILURE;
    }

    destination = input;

    for (size_t i = 0; i < argument_count; ++i) {
        size_t length = lengths[i];

        if (length != 0U) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination, argv[i + 1U], length);
            destination += length;
        }

        if (i + 1U < argument_count) {
            *destination++ = ' ';
        }
    }

    *destination = '\0';
    free(lengths);

    if (find_sequences(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}