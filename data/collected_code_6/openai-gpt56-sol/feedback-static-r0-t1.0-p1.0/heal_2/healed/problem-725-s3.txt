#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

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
        regoff_t match_start = matches[1].rm_so;
        regoff_t match_end = matches[1].rm_eo;
        regoff_t full_match_end = matches[0].rm_eo;
        size_t cursor_length;
        size_t start;
        size_t end;
        size_t advance;
        size_t length;
        char *value;

        if (match_start < 0 || match_end < match_start ||
            full_match_end <= 0 || matches[0].rm_so < 0) {
            regfree(&regex);
            return -1;
        }

        if ((uintmax_t)match_start > SIZE_MAX ||
            (uintmax_t)match_end > SIZE_MAX ||
            (uintmax_t)full_match_end > SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        start = (size_t)match_start;
        end = (size_t)match_end;
        advance = (size_t)full_match_end;
        cursor_length = strlen(cursor);

        if (start > end || end > cursor_length ||
            advance > cursor_length || advance == 0) {
            regfree(&regex);
            return -1;
        }

        length = end - start;
        if (length == SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        if (length != 0) {
            memcpy(value, cursor + start, length);
        }
        value[length] = '\0';

        if (fwrite(value, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        cursor += advance;

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