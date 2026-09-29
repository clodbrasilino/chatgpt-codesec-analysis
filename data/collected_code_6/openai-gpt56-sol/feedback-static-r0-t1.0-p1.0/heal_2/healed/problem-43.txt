#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *context)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", context);
        return;
    }

    regerror(status, regex, message, size);
    fprintf(stderr, "%s: %s\n", context, message);
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
        report_regex_error(status, &regex, "regcomp failed");
        return -1;
    }

    while ((status = regexec(&regex, cursor, 5, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;
        regoff_t length;

        if (start < 0 || end <= start) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return -1;
        }

        length = end - start;
        if (length > INT_MAX ||
            printf("%.*s\n", (int)length, cursor + start) < 0) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return -1;
        }

        if (count == INT_MAX) {
            fprintf(stderr, "Match count overflow\n");
            regfree(&regex);
            return -1;
        }

        ++count;
        cursor += end;
    }

    if (status != REG_NOMATCH) {
        report_regex_error(status, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return count;
}

int main(int argc, const char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}