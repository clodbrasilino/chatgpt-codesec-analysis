#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t pos;
    size_t out;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    out = 0;
    while (pos <= len) {
        ret = regexec(&regex, input + pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = len - pos;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out, input + pos, remaining);
            out += remaining;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + out, input + pos, (size_t)match.rm_so);
        out += (size_t)match.rm_so;
        pos += (size_t)match.rm_eo;
        if (match.rm_eo == match.rm_so) {
            break;
        }
    }

    result[out] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "HelloWORLDthisISaTEST";
    char *cleaned;

    cleaned = remove_uppercase(test);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }
    if (printf("Cleaned:  %s\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}