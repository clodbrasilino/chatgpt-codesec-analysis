#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len >= SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *src = input;
    char *dst = result;
    size_t dst_remaining = len + 1;
    regmatch_t match;

    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            if (match_start >= dst_remaining) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, match_start);
            dst += match_start;
            dst_remaining -= match_start;
        }

        if (dst_remaining < 2) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        *dst++ = ' ';
        dst_remaining--;

        src += match_end;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining = strlen(src);
    if (remaining >= dst_remaining) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, remaining + 1);

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test = "This  is   a    test   string";
    char *cleaned = remove_multiple_spaces(test);

    if (cleaned != NULL) {
        printf("Original: '%s'\n", test);
        printf("Cleaned:  '%s'\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}