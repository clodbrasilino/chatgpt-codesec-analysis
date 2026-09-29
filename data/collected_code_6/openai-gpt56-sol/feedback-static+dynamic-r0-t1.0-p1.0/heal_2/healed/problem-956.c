#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

static int print_segment(const char *text, regoff_t length)
{
    if (text == NULL || length < 0 ||
        (unsigned long long)length > (unsigned long long)INT_MAX) {
        return -1;
    }

    return printf("%.*s\n", (int)length, text) < 0 ? -1 : 0;
}

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            status = printf("%s\n", cursor) < 0 ? -1 : 0;
            regfree(&regex);
            return status;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so > 0 && print_segment(cursor, match.rm_so) != 0) {
            regfree(&regex);
            return -1;
        }

        cursor += match.rm_so;

        status = regexec(&regex, cursor + 1, 1, &match, 0);

        if (status == REG_NOMATCH) {
            status = printf("%s\n", cursor) < 0 ? -1 : 0;
            regfree(&regex);
            return status;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if (print_segment(cursor, match.rm_so + 1) != 0) {
            regfree(&regex);
            return -1;
        }

        cursor += match.rm_so + 1;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (split_at_uppercase(argv[1]) != 0) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}