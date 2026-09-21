#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#define MAX_STRING_LEN 1024

char *snake_to_camel(const char *input) {
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    size_t result_len = 0;
    size_t result_capacity = 0;
    const char *cursor = input;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    result_capacity = strnlen(input, MAX_STRING_LEN) + 1;
    if (result_capacity > MAX_STRING_LEN) {
        return NULL;
    }

    result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0) {
            size_t prefix_len = (size_t)match.rm_so;
            size_t needed = result_len + prefix_len + 2;
            
            if (needed > result_capacity) {
                size_t new_capacity = needed * 2;
                if (new_capacity > MAX_STRING_LEN + 1) {
                    new_capacity = MAX_STRING_LEN + 1;
                }
                if (new_capacity < needed) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                char *new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            
            if (prefix_len > 0) {
                /* Possible weaknesses found:
                 *  outer condition: result_len+prefix_len<result_capacity
                 */
                if (result_len + prefix_len < result_capacity) {
                    /* Possible weaknesses found:
                     *  'copy_len' is assigned value 'prefix_len' here.
                     */
                    size_t copy_len = prefix_len;
                    /* Possible weaknesses found:
                     *  opposite inner condition: result_len+copy_len>=result_capacity
                     *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
                     */
                    if (result_len + copy_len >= result_capacity) {
                        copy_len = result_capacity - result_len - 1;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_len, cursor, copy_len);
                    result_len += copy_len;
                } else {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
            }
            
            if (result_len < result_capacity) {
                result[result_len++] = (char)toupper((unsigned char)cursor[match.rm_eo - 1]);
                result[result_len] = '\0';
            }
            cursor += match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, MAX_STRING_LEN);
            size_t needed = result_len + remaining + 1;
            
            if (needed > result_capacity) {
                size_t new_capacity = needed;
                if (new_capacity > MAX_STRING_LEN + 1) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                char *new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
            }
            
            if (remaining > 0) {
                /* Possible weaknesses found:
                 *  outer condition: result_len+remaining<result_capacity
                 */
                if (result_len + remaining < result_capacity) {
                    /* Possible weaknesses found:
                     *  'copy_len' is assigned value 'remaining' here.
                     */
                    size_t copy_len = remaining;
                    /* Possible weaknesses found:
                     *  opposite inner condition: result_len+copy_len>=result_capacity
                     *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
                     */
                    if (result_len + copy_len >= result_capacity) {
                        copy_len = result_capacity - result_len - 1;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_len, cursor, copy_len);
                    result_len += copy_len;
                } else {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
            }
            result[result_len] = '\0';
            break;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string_example",
        "single",
        "multiple__underscores",
        NULL
    };
    int i;

    for (i = 0; test_cases[i] != NULL; i++) {
        char *camel = snake_to_camel(test_cases[i]);
        if (camel != NULL) {
            printf("Input:  %s\n", test_cases[i]);
            printf("Output: %s\n\n", camel);
            free(camel);
        } else {
            printf("Conversion failed for: %s\n\n", test_cases[i]);
        }
    }

    return 0;
}