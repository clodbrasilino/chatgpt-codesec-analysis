#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *input)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:upper:]][[:lower:]]+)";

    regex_t regex;
    regmatch_t matches[3];
    const char *cursor = input;
    int status;
    int found = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return -1;
    }

    while ((status = regexec(&regex, cursor, 3, matches, 0)) == 0) {
        regoff_t match_start = matches[2].rm_so;
        regoff_t match_end = matches[2].rm_eo;
        size_t length;

        if (match_start < 0 || match_end < match_start) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match_end - match_start);

        if (fwrite(cursor + match_start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        found = 1;
        cursor += match_end;
    }

    if (status != REG_NOMATCH) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "Regex matching failed: %s\n", error_message);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
}

int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}