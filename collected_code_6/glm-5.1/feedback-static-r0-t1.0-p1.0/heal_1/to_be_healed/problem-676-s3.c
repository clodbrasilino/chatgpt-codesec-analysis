#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
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
    size_t max_matches = strlen(input);
    if (max_matches == 0) {
        regfree(&regex);
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_size = strlen(input) + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        free(matches);
        return NULL;
    }

    size_t result_idx = 0;
    size_t search_idx = 0;
    const char *str_ptr = input;

    while (1) {
        ret = regexec(&regex, str_ptr, max_matches, matches, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(&result[result_idx], str_ptr);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result_idx += strlen(str_ptr);
            break;
        }

        if (ret != 0) {
            free(result);
            free(matches);
            regfree(&regex);
            return NULL;
        }

        if (matches[0].rm_so == -1) {
            break;
        }

        /* Possible weaknesses found:
         *  Value stored to 'match_len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
         */
        size_t match_len = matches[0].rm_eo - matches[0].rm_so;
        size_t copy_len = matches[0].rm_so;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(&result[result_idx], str_ptr, copy_len);
        result_idx += copy_len;

        str_ptr += matches[0].rm_eo;
        search_idx += matches[0].rm_eo;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (search_idx >= strlen(input)) {
            break;
        }
    }

    result[result_idx] = '\0';

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        final_result = result;
    }

    regfree(&regex);
    free(matches);

    return final_result;
}

int main(void) {
    char *result1 = remove_non_alphanumeric("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alphanumeric("Another@test*string");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    /* Possible weaknesses found:
     *  Variable 'result3' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'result3=remove_non_alphanumeric(NULL)', assigned value is 0
     *  Calling function 'remove_non_alphanumeric' returns 0
     */
    char *result3 = remove_non_alphanumeric(NULL);
    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     */
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    }

    return 0;
}