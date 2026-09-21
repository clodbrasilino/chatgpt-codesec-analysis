#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

int remove_non_alphanumeric(char *text)
{
    regex_t regex;
    regmatch_t match;
    char *filtered;
    const char *cursor;
    size_t length;
    size_t remaining;
    size_t write_index = 0;
    int status;

    if (text == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(text);
    if (length == SIZE_MAX) {
        return -1;
    }

    status = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    filtered = malloc(length + 1);
    if (filtered == NULL) {
        regfree(&regex);
        return -1;
    }

    cursor = text;
    remaining = length;

    while (remaining > 0) {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(filtered + write_index, cursor, remaining);
            write_index += remaining;
            break;
        }

        if (status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining) {
            free(filtered);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(filtered + write_index, cursor, (size_t)match.rm_so);
        write_index += (size_t)match.rm_so;
        cursor += (size_t)match.rm_eo;
        remaining -= (size_t)match.rm_eo;
    }

    filtered[write_index] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(text, filtered, write_index + 1);

    free(filtered);
    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <text>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (remove_non_alphanumeric(argv[1]) != 0) {
        if (fprintf(stderr, "Failed to process input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}