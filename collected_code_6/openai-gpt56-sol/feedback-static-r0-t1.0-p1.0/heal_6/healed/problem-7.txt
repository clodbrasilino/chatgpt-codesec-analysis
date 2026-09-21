#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message;

    if (size == 0) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    (void)regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_words(const char *text)
{
    static const char pattern[] = "[[:alnum:]_]{4,}";
    regex_t regex;
    const char *cursor;
    int status;

    if (text == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, NULL, "regcomp");
        return EXIT_FAILURE;
    }

    cursor = text;

    while (*cursor != '\0') {
        regmatch_t match;
        size_t remaining;
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
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        remaining = strlen(cursor);
        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > remaining || end > remaining || end <= start) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        length = end - start;

        if (fwrite(cursor + start, sizeof *cursor, length, stdout) != length) {
            fprintf(stderr, "Failed to write output\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        cursor += end;
    }

    regfree(&regex);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}