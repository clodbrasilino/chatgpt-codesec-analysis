#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int extract_quoted_values(const char *input)
{
    static const char pattern[] = "\"([^\"]*)\"";
    const char *current;
    regex_t regex;
    regmatch_t matches[2];
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    current = input;

    while ((status = regexec(&regex, current, 2, matches, 0)) == 0) {
        regoff_t match_start = matches[0].rm_so;
        regoff_t match_end = matches[0].rm_eo;
        regoff_t capture_start = matches[1].rm_so;
        regoff_t capture_end = matches[1].rm_eo;
        size_t remaining = strlen(current);
        size_t start;
        size_t end;
        size_t length;
        size_t consumed;
        char *value;

        if (match_start < 0 || match_end <= match_start ||
            capture_start < 0 || capture_end < capture_start) {
            regfree(&regex);
            return -1;
        }

        start = (size_t)capture_start;
        end = (size_t)capture_end;
        consumed = (size_t)match_end;

        if (start > remaining || end > remaining || consumed > remaining) {
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
            memcpy(value, current + start, length);
        }
        value[length] = '\0';

        if (fwrite(value, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        current += consumed;
    }

    regfree(&regex);
    return status == REG_NOMATCH ? 0 : -1;
}

int main(void)
{
    const char *input =
        "The values are \"first\", \"second value\", and \"third\".";

    if (extract_quoted_values(input) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}