#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
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

static int find_sequences(const char *text)
{
    static const char pattern[] =
        "(^|[^a-z_])([a-z]+(_[a-z]+)+)([^a-z_]|$)";
    regex_t regex;
    regmatch_t matches[5];
    const char *cursor = text;
    int status;
    int count = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp");
        return -1;
    }

    while ((status = regexec(&regex, cursor, 5, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;
        regoff_t length;

        if (start < 0 || end <= start) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return -1;
        }

        length = end - start;
        if (length > INT_MAX) {
            fprintf(stderr, "Match is too long to print\n");
            regfree(&regex);
            return -1;
        }

        if (printf("%.*s\n", (int)length, cursor + start) < 0) {
            fprintf(stderr, "Failed to write output\n");
            regfree(&regex);
            return -1;
        }

        if (count == INT_MAX) {
            fprintf(stderr, "Too many matches\n");
            regfree(&regex);
            return -1;
        }

        ++count;
        cursor += end;
    }

    if (status != REG_NOMATCH) {
        report_regex_error(status, &regex, "regexec");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return count;
}

int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}