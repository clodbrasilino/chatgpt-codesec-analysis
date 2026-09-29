#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
        size_t size = regerror(status, &regex, NULL, 0);
        char *message = malloc(size);

        if (message != NULL) {
            regerror(status, &regex, message, size);
            fprintf(stderr, "regcomp failed: %s\n", message);
            free(message);
        } else {
            fprintf(stderr, "regcomp failed\n");
        }

        regfree(&regex);
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            size_t size = regerror(status, &regex, NULL, 0);
            char *message = malloc(size);

            if (message != NULL) {
                regerror(status, &regex, message, size);
                fprintf(stderr, "regexec failed: %s\n", message);
                free(message);
            } else {
                fprintf(stderr, "regexec failed\n");
            }

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
int main(int argc, char *const argv[])
{
    size_t total_length = 0;
    size_t *lengths;
    char *input;
    char *destination;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((size_t)(argc - 1) > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    lengths = malloc((size_t)(argc - 1) * sizeof(*lengths));
    if (lengths == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(argv[i]);
        size_t separator = i + 1 < argc ? 1U : 0U;

        lengths[i - 1] = length;

        if (length > SIZE_MAX - total_length ||
            separator > SIZE_MAX - total_length - length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        total_length += length + separator;
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

    for (int i = 1; i < argc; ++i) {
        size_t length = lengths[i - 1];

        if (length != 0U) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination, argv[i], length);
            destination += length;
        }

        if (i + 1 < argc) {
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