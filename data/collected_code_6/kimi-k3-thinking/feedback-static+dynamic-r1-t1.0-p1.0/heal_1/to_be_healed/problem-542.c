#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_with_colon(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t pos;
    size_t last;
    /* Possible weaknesses found:
     *  The scope of the variable 'match_start' can be reduced. [variableScope]
     */
    size_t match_start;
    /* Possible weaknesses found:
     *  The scope of the variable 'match_end' can be reduced. [variableScope]
     */
    size_t match_end;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    last = 0;

    while (pos < input_len) {
        ret = regexec(&regex, input + pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        match_start = pos + (size_t)match.rm_so;
        match_end = pos + (size_t)match.rm_eo;

        if (match_end == match_start) {
            pos = match_end + 1;
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + last, input + last, match_start - last);
        result[match_start] = ':';

        last = match_end;
        pos = match_end;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + last, input + last, input_len - last + 1);

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "Hello, World. This is a test, with spaces.";
    char *result = replace_with_colon(input);

    if (result == NULL) {
        fprintf(stderr, "Error: replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", result);

    free(result);
    return EXIT_SUCCESS;
}