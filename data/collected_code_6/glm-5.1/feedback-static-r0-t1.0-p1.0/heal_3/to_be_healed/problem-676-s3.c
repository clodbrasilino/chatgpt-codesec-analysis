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

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == 0) {
        regfree(&regex);
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    char *result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    size_t search_idx = 0;
    const char *str_ptr = input;
    regmatch_t match;

    while (search_idx < input_len) {
        ret = regexec(&regex, str_ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t copy_len = input_len - search_idx;
            if (result_idx + copy_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, str_ptr, copy_len);
                result_idx += copy_len;
            }
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t copy_len = match.rm_so;
        if (copy_len > 0) {
            if (result_idx + copy_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, str_ptr, copy_len);
                result_idx += copy_len;
            }
        }

        str_ptr += match.rm_eo;
        search_idx += match.rm_eo;
    }

    result[result_idx] = '\0';

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        final_result = result;
    }

    regfree(&regex);

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
     *  Calling function 'remove_non_alphanumeric' returns 0
     *  Assignment 'result3=remove_non_alphanumeric(NULL)', assigned value is 0
     */
    const char *result3 = remove_non_alphanumeric(NULL);
    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result3==NULL' is always true
     */
    if (result3 == NULL) {
        printf("Handled NULL input safely\n");
    }

    return 0;
}