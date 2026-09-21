#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
        regoff_t start = matches[1].rm_so;
        regoff_t end = matches[1].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);
        size_t length;
        char *value;

        if (start < 0 || end < start ||
            (uintmax_t)end > (uintmax_t)remaining) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(end - start);

        if (length > SIZE_MAX - 1) {
            regfree(&regex);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        if (length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(value, cursor + (size_t)start, length);
        }
        value[length] = '\0';

        if (fwrite(value, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);

        if (matches[0].rm_eo <= 0 ||
            (uintmax_t)matches[0].rm_eo > (uintmax_t)remaining) {
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)matches[0].rm_eo;
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