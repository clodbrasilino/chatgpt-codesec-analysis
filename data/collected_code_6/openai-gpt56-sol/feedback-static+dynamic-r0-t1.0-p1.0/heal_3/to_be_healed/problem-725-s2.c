#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    cursor = input;

    while ((status = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t cursor_length = strlen(cursor);
        size_t match_start;
        size_t match_end;
        size_t value_start;
        size_t value_end;
        size_t value_length;
        char *value;

        if (matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < matches[1].rm_so) {
            regfree(&regex);
            return -1;
        }

        match_start = (size_t)matches[0].rm_so;
        match_end = (size_t)matches[0].rm_eo;
        value_start = (size_t)matches[1].rm_so;
        value_end = (size_t)matches[1].rm_eo;

        if (match_start > cursor_length ||
            match_end > cursor_length ||
            value_start > cursor_length ||
            value_end > cursor_length ||
            value_start < match_start ||
            value_end > match_end) {
            regfree(&regex);
            return -1;
        }

        value_length = value_end - value_start;

        if (value_length == SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        value = malloc(value_length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        if (value_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(value, cursor + value_start, value_length);
        }
        value[value_length] = '\0';

        if (fputs(value, stdout) == EOF || fputc('\n', stdout) == EOF) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        cursor += match_end;
    }

    regfree(&regex);
    return status == REG_NOMATCH ? 0 : -1;
}

int main(void)
{
    const char input[] =
        "name=\"Alice\" city=\"London\" message=\"Hello, world!\"";

    if (extract_quoted_values(input) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}