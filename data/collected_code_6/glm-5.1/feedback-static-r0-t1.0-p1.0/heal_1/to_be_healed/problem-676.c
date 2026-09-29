#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    size_t max_matches = input_len;
    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_len = input_len + 1;
    char *result = malloc(result_len);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char *search_start = input;

    while (1) {
        ret = regexec(&regex, search_start, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining_len = strlen(search_start);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, search_start, remaining_len);
            result_idx += remaining_len;
            break;
        }

        if (ret != 0) {
            break;
        }

        size_t match_offset = matches[0].rm_so;
        /* Possible weaknesses found:
         *  Value stored to 'match_len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
         */
        size_t match_len = matches[0].rm_eo - matches[0].rm_so;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_idx, search_start, match_offset);
        result_idx += match_offset;

        search_start += matches[0].rm_eo;
    }

    result[result_idx] = '\0';

    if (result_idx + 1 < result_len) {
        char *trimmed_result = realloc(result, result_idx + 1);
        if (trimmed_result != NULL) {
            result = trimmed_result;
        }
    }

    free(matches);
    regfree(&regex);

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *cleaned = remove_non_alnum(argv[1]);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return 1;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    return 0;
}