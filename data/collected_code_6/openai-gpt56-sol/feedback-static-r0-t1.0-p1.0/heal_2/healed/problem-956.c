#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int print_segment(const char *text, size_t length)
{
    while (length > 0U) {
        int chunk = length > (size_t)INT_MAX ? INT_MAX : (int)length;

        if (printf("%.*s", chunk, text) < 0) {
            return -1;
        }

        text += (size_t)chunk;
        length -= (size_t)chunk;
    }

    return putchar('\n') == EOF ? -1 : 0;
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
        status = regexec(&regex, cursor, 1U, &match, 0);

        if (status == REG_NOMATCH) {
            if (printf("%s\n", cursor) < 0) {
                regfree(&regex);
                return -1;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so > 0 &&
            print_segment(cursor, (size_t)match.rm_so) != 0) {
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match.rm_so;

        status = regexec(&regex, cursor + 1, 1U, &match, 0);

        if (status == REG_NOMATCH) {
            if (printf("%s\n", cursor) < 0) {
                regfree(&regex);
                return -1;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 ||
            print_segment(cursor, (size_t)match.rm_so + 1U) != 0) {
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match.rm_so + 1U;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL
                                  ? argv[0]
                                  : "program";

        (void)fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    if (split_at_uppercase(argv[1]) != 0) {
        (void)fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}