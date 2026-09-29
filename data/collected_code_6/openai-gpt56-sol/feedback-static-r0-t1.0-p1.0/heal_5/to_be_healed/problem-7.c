#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
{
    size_t size;
    char *message;

    size = regerror(status, regex, NULL, 0);
    if (size == 0 || size > SIZE_MAX) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_words(const char *text, size_t text_length)
{
    static const char pattern[] = "[[:alnum:]_]{4,}";
    regex_t regex;
    char *buffer;
    char *cursor;
    size_t remaining;
    int status;

    if (text == NULL || text_length == SIZE_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(text_length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    if (text_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, text, text_length);
    }
    buffer[text_length] = '\0';

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, NULL, "regcomp");
        free(buffer);
        return EXIT_FAILURE;
    }

    cursor = buffer;
    remaining = text_length;

    while (remaining > 0) {
        regmatch_t match;
        size_t start;
        size_t end;
        size_t length;

        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            free(buffer);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo < 0) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            free(buffer);
            return EXIT_FAILURE;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > remaining || end > remaining || start >= end) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            free(buffer);
            return EXIT_FAILURE;
        }

        length = end - start;

        if (fwrite(cursor + start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            regfree(&regex);
            free(buffer);
            return EXIT_FAILURE;
        }

        cursor += end;
        remaining -= end;
    }

    regfree(&regex);
    free(buffer);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program;
    size_t text_length;

    program = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_length = strlen(argv[1]);
    return find_words(argv[1], text_length);
}