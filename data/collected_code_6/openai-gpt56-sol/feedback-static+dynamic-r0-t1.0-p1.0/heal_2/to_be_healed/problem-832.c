#include <errno.h>
#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool extract_max_value(const char *text, intmax_t *maximum)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    bool found = false;
    intmax_t max_value = 0;
    int status;

    if (text == NULL || maximum == NULL) {
        return false;
    }

    status = regcomp(&regex, "[+-]?[0-9]+", REG_EXTENDED);
    if (status != 0) {
        return false;
    }

    cursor = text;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        const char *start = cursor + match.rm_so;
        char *end = NULL;
        intmax_t value;

        errno = 0;
        value = strtoimax(start, &end, 10);

        if (end > start && errno != ERANGE) {
            if (!found || value > max_value) {
                max_value = value;
                found = true;
            }
        }

        if (match.rm_eo > 0) {
            cursor += match.rm_eo;
        } else if (*cursor != '\0') {
            ++cursor;
        } else {
            break;
        }
    }

    regfree(&regex);

    if (status != REG_NOMATCH || !found) {
        return false;
    }

    *maximum = max_value;
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    intmax_t maximum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!extract_max_value(argv[1], &maximum)) {
        fprintf(stderr, "No valid numeric value found\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIdMAX "\n", maximum);
    return EXIT_SUCCESS;
}