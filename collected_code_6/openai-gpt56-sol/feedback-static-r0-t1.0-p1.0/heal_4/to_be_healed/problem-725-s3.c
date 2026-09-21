#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    size_t remaining;
    int count = 0;
    int result;

    if (input == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining = strlen(input);

    result = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    cursor = input;

    for (;;) {
        regoff_t match_start;
        regoff_t match_end;
        regoff_t full_match_start;
        regoff_t full_match_end;
        size_t start;
        size_t end;
        size_t advance;
        size_t length;

        result = regexec(&regex, cursor, 2, matches, 0);
        if (result != 0) {
            break;
        }

        full_match_start = matches[0].rm_so;
        full_match_end = matches[0].rm_eo;
        match_start = matches[1].rm_so;
        match_end = matches[1].rm_eo;

        if (full_match_start < 0 ||
            full_match_end <= full_match_start ||
            match_start < full_match_start ||
            match_end < match_start ||
            match_end > full_match_end) {
            regfree(&regex);
            return -1;
        }

        if ((uintmax_t)full_match_end > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match_start > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match_end > (uintmax_t)SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        start = (size_t)match_start;
        end = (size_t)match_end;
        advance = (size_t)full_match_end;

        if (start > remaining ||
            end > remaining ||
            advance > remaining) {
            regfree(&regex);
            return -1;
        }

        length = end - start;

        if (length > 0 &&
            fwrite(cursor + start, 1, length, stdout) != length) {
            regfree(&regex);
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += advance;
        remaining -= advance;

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
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(argv[1]);
    if (count < 0) {
        fprintf(stderr, "Failed to extract quoted values\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}