#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    static const char pattern[] = "(^|[^a-z_])([a-z]+_[a-z]+)($|[^a-z_])";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int status;
    int found = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "regcomp failed: %s\n", error_message);
        return -1;
    }

    while ((status = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;
        regoff_t length;

        if (start < 0 || end <= start) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        length = end - start;
        if (length > INT_MAX) {
            fprintf(stderr, "Match is too long\n");
            regfree(&regex);
            return -1;
        }

        if (printf("%.*s\n", (int)length, cursor + start) < 0) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return -1;
        }

        cursor += end;
        ++found;
    }

    if (status != REG_NOMATCH) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "regexec failed: %s\n", error_message);
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