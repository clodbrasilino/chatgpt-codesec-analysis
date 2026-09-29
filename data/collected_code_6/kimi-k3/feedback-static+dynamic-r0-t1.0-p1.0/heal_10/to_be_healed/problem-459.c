#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *str, size_t str_len)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t result_len = 0;
    size_t result_capacity = 0;
    size_t i = 0;
    int ret;

    if (str == NULL) {
        return NULL;
    }

    result_capacity = str_len + 1;
    result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (i < str_len) {
        ret = regexec(&regex, str + i, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = str_len - i;
            size_t required = result_len + remaining + 1;
            if (required > result_capacity) {
                char *new_result = realloc(result, required);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = required;
            }
            if (remaining > 0) {
                /* Possible weaknesses found:
                 *  Assuming that condition 'result_len+remaining>=result_capacity' is not redundant
                 */
                if (result_len + remaining >= result_capacity) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (result_len + remaining > result_capacity - 1) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 *  Condition 'result_len+remaining>result_capacity' is always false [knownConditionTrueFalse]
                 *  Condition 'result_len+remaining>result_capacity' is always false
                 */
                if (result_len + remaining > result_capacity) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, str + i, remaining);
                result_len += remaining;
            }
            result[result_len] = '\0';
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = i + match.rm_so;
        size_t match_end = i + match.rm_eo;
        size_t prefix_len = match_start - i;

        size_t required = result_len + prefix_len + 1;
        if (required > result_capacity) {
            char *new_result = realloc(result, required);
            if (new_result == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
            result_capacity = required;
        }
        if (prefix_len > 0) {
            /* Possible weaknesses found:
             *  Assuming that condition 'result_len+prefix_len>=result_capacity' is not redundant
             */
            if (result_len + prefix_len >= result_capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (result_len + prefix_len > result_capacity - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition 'result_len+prefix_len>result_capacity' is always false [knownConditionTrueFalse]
             *  Condition 'result_len+prefix_len>result_capacity' is always false
             */
            if (result_len + prefix_len > result_capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, str + i, prefix_len);
            result_len += prefix_len;
        }
        result[result_len] = '\0';

        i = match_end;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_string = "HelloWORLDThisISaTESTString";
    size_t test_len = strnlen(test_string, 1024);
    char *result = remove_uppercase_substrings(test_string, test_len);

    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", result);

    free(result);
    return EXIT_SUCCESS;
}