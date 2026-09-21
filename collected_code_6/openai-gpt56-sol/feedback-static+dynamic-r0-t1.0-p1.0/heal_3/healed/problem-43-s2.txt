#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int error_code, const regex_t *regex,
                               const char *context)
{
    size_t size = regerror(error_code, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fprintf(stderr, "%s\n", context);
        return;
    }

    regerror(error_code, regex, message, size);
    fprintf(stderr, "%s: %s\n", context, message);
    free(message);
}

static int find_sequences(const char *text)
{
    static const char pattern[] =
        "(^|[^a-z_])([a-z]+_[a-z]+)([^a-z_]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int result;
    int found = 0;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex, "regcomp failed");
        return -1;
    }

    while ((result = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        regoff_t match_start = matches[2].rm_so;
        regoff_t match_end = matches[2].rm_eo;
        size_t length;

        if (match_start < 0 || match_end < match_start) {
            fputs("Invalid regex match\n", stderr);
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match_end - match_start);

        if (length > (size_t)INT_MAX) {
            fputs("Match is too long\n", stderr);
            regfree(&regex);
            return -1;
        }

        if (printf("%.*s\n", (int)length,
                   cursor + (size_t)match_start) < 0) {
            fputs("Output failed\n", stderr);
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match_end;

        if (found == INT_MAX) {
            fputs("Too many matches\n", stderr);
            regfree(&regex);
            return -1;
        }

        ++found;
    }

    if (result != REG_NOMATCH) {
        report_regex_error(result, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
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