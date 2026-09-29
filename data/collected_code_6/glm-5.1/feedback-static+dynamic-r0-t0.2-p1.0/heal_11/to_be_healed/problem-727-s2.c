#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    size_t result_size = 0;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t search_start = 0;
    regmatch_t match;

    while (1) {
        int exec_ret = regexec(&regex, input + search_start, 1, &match, 0);
        if (exec_ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining_len = strlen(input + search_start);
            if (remaining_len > 0) {
                /* Possible weaknesses found:
                 *  required_size is assigned 'result_idx+remaining_len+1' here.
                 */
                size_t required_size = result_idx + remaining_len + 1;
                char *new_result = realloc(result, required_size);
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                /* Possible weaknesses found:
                 *  result_size is assigned 'required_size' here.
                 */
                result_size = required_size;
                /* Possible weaknesses found:
                 *  Condition 'result_idx+remaining_len<=result_size' is always true
                 *  Condition 'result_idx+remaining_len<=result_size' is always true [knownConditionTrueFalse]
                 */
                if (result_idx + remaining_len <= result_size) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_idx, input + search_start, remaining_len);
                }
            }
            result_idx += remaining_len;
            break;
        } else if (exec_ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t match_start = search_start + match.rm_so;
        size_t match_end = search_start + match.rm_eo;

        size_t copy_len = match_start - search_start;
        if (copy_len > 0) {
            size_t required_size = result_idx + copy_len + 1;
            if (required_size > result_size) {
                char *new_result = realloc(result, required_size);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_size = required_size;
            }
            if (result_idx + copy_len <= result_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, input + search_start, copy_len);
            }
        }
        result_idx += copy_len;

        search_start = match_end;
    }

    if (result_idx + 1 > result_size) {
        char *new_result = realloc(result, result_idx + 1);
        if (new_result != NULL) {
            result = new_result;
            result_size = result_idx + 1;
        }
    }

    if (result_idx < result_size) {
        result[result_idx] = '\0';
    }

    char *trimmed_result = realloc(result, result_idx + 1);
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    regfree(&regex);

    return result;
}

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___test___");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = remove_non_alnum(NULL);
    (void)result4;

    return 0;
}