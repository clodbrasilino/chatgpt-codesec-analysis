#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
{
    char buffer[256];
    size_t required;

    required = regerror(status, regex, buffer, sizeof buffer);

    if (required == 0) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
    } else if (required <= sizeof buffer) {
        fprintf(stderr, "%s failed: %s\n", operation, buffer);
    } else {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
    }
}

static int find_words(const char *text)
{
    static const char pattern[] = "[[:alnum:]_]{4,}";
    regex_t regex;
    const char *cursor;
    size_t remaining;
    int status;

    if (text == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    remaining = strlen(text);

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, NULL, "regcomp");
        return EXIT_FAILURE;
    }

    cursor = text;

    while (remaining != 0) {
        regmatch_t match;
        uintmax_t raw_start;
        uintmax_t raw_end;
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

        raw_start = (uintmax_t)match.rm_so;
        raw_end = (uintmax_t)match.rm_eo;

        if (raw_start > SIZE_MAX || raw_end > SIZE_MAX) {
            fprintf(stderr, "Regular-expression match is too large\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        start = (size_t)raw_start;
        end = (size_t)raw_end;

        if (start > remaining || end > remaining || end <= start) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        length = end - start;

        if (fwrite(cursor + start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Failed to write output\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        cursor += end;
        remaining -= end;
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