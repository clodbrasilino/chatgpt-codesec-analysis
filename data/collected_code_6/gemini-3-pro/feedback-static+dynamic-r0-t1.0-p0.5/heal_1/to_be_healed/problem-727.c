#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_special_chars(const char *input, char **output) {
    if (!input || !output) {
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    *output = (char *)malloc(len + 1);
    if (!*output) {
        regfree(&regex);
        return -1;
    }

    size_t out_idx = 0;
    regmatch_t pmatch[1];
    const char *cursor = input;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        if (match_start > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(*output + out_idx, cursor, match_start);
            out_idx += match_start;
        }

        cursor += match_end;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining = strlen(cursor);
    if (remaining > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*output + out_idx, cursor, remaining);
        out_idx += remaining;
    }

    (*output)[out_idx] = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    if (remove_special_chars(input, &output) == 0) {
        printf("Original: %s\n", input);
        printf("Cleaned:  %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}