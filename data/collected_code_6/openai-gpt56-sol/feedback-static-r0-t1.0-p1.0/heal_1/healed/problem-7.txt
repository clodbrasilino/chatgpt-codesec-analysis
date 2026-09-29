#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void report_regex_error(int status, const regex_t *regex, const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_words(const char *text)
{
    static const char pattern[] = "([[:alnum:]_]{4,})";
    regex_t regex;
    regmatch_t match;
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp");
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t end = (size_t)match.rm_eo;
            size_t length = end - start;

            if (fwrite(cursor + start, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                fprintf(stderr, "Failed to write output\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            cursor += end;
        }
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}