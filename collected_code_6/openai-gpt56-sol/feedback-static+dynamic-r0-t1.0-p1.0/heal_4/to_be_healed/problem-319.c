#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(const char *operation, int status,
                               const regex_t *regex)
{
    size_t length = regerror(status, regex, NULL, 0);
    char *message;

    if (length == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    message = malloc(length);
    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    regerror(status, regex, message, length);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_five_character_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]{5})($|[^[:alnum:]_])";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor;
    int status;

    if (text == NULL) {
        return 1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error("regcomp", status, &regex);
        return 1;
    }

    cursor = text;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error("regexec", status, &regex);
            regfree(&regex);
            return 1;
        }

        if (matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[2].rm_so < matches[0].rm_so ||
            matches[2].rm_eo < matches[2].rm_so ||
            matches[2].rm_eo > matches[0].rm_eo) {
            regfree(&regex);
            return 1;
        }

        {
            size_t word_length =
                (size_t)(matches[2].rm_eo - matches[2].rm_so);

            if (fwrite(cursor + matches[2].rm_so, 1, word_length, stdout) !=
                    word_length ||
                fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return 1;
            }
        }

        cursor += matches[0].rm_eo;
    }

    regfree(&regex);

    return fflush(stdout) == EOF ? 1 : 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    size_t total_length = 1;
    size_t position = 0;
    const char *const *arguments = (const char *const *)argv;
    char *text;
    int result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && arguments != NULL && arguments[0] != NULL
                    ? arguments[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (arguments == NULL) {
        fputs("Invalid argument vector\n", stderr);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length;
        size_t separator = i + 1 < argc ? 1U : 0U;

        if (arguments[i] == NULL) {
            fputs("Invalid argument\n", stderr);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(arguments[i]);

        if (length > SIZE_MAX - total_length ||
            separator > SIZE_MAX - total_length - length) {
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }

        total_length += length + separator;
    }

    text = malloc(total_length);
    if (text == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(arguments[i]);
        size_t available = total_length - position;

        if (available == 0 || length >= available) {
            free(text);
            fputs("Input size changed unexpectedly\n", stderr);
            return EXIT_FAILURE;
        }

        if (length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(text + position, arguments[i], length);
            position += length;
        }

        if (i + 1 < argc) {
            if (position >= total_length - 1) {
                free(text);
                fputs("Input size changed unexpectedly\n", stderr);
                return EXIT_FAILURE;
            }

            text[position++] = ' ';
        }
    }

    if (position >= total_length) {
        free(text);
        fputs("Input size changed unexpectedly\n", stderr);
        return EXIT_FAILURE;
    }

    text[position] = '\0';
    result = find_five_character_words(text);
    free(text);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}