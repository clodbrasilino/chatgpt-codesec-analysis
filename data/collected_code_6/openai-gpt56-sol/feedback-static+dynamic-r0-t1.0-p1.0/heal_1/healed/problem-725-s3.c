#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    int count = 0;
    int result;

    if (input == NULL) {
        return -1;
    }

    result = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    cursor = input;

    while ((result = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        regoff_t start = matches[1].rm_so;
        regoff_t end = matches[1].rm_eo;
        regoff_t match_end = matches[0].rm_eo;
        size_t length;

        if (start < 0 || end < start || match_end <= 0) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(end - start);

        if (length > 0 &&
            fwrite(cursor + (size_t)start, 1, length, stdout) != length) {
            regfree(&regex);
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match_end;

        if (count == INT_MAX) {
            regfree(&regex);
            return -1;
        }

        ++count;
    }

    regfree(&regex);

    return result == REG_NOMATCH ? count : -1;
}

int main(int argc, char *argv[])
{
    int count;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(argv[1]);
    if (count < 0) {
        fputs("Failed to extract quoted values\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}