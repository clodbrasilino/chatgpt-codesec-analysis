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
        const regoff_t start = matches[2].rm_so;
        const regoff_t end = matches[2].rm_eo;

        if (start < 0 || end < start) {
            regfree(&regex);
            return -1;
        }

        if (printf("%.*s\n", (int)(end - start), cursor + start) < 0) {
            regfree(&regex);
            return -1;
        }

        found = 1;
        cursor += end;
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

int main(int argc, const char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}