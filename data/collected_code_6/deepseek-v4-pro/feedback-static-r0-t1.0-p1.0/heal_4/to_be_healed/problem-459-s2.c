#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z]+";
    size_t input_len;
    char *result;
    char *tmp;
    int ret;
    const char *cursor;
    size_t result_len;
    size_t remaining;
    size_t prefix_len;
    
    if (!input) return NULL;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len == 0) {
        result = malloc(1);
        if (result) result[0] = '\0';
        return result;
    }
    
    result = malloc(input_len + 1);
    if (!result) return NULL;
    result[0] = '\0';
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        free(result);
        return NULL;
    }
    
    cursor = input;
    result_len = 0;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'cursor<input+input_len' is not redundant
     */
    while (cursor < input + input_len) {
        if (regexec(&regex, cursor, 1, &match, 0) == 0 && match.rm_so != -1) {
            prefix_len = (size_t)match.rm_so;
            if (prefix_len > 0) {
                if (result_len + prefix_len > input_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, prefix_len);
                result_len += prefix_len;
            }
            if (cursor + match.rm_eo <= input + input_len) {
                cursor += match.rm_eo;
            } else {
                break;
            }
        } else {
            /* Possible weaknesses found:
             *  Assignment 'remaining=(unsigned long)(input+input_len-cursor)', assigned value is greater than 0
             */
            remaining = (size_t)(input + input_len - cursor);
            /* Possible weaknesses found:
             *  Condition 'remaining>0' is always true
             *  Condition 'remaining>0' is always true [knownConditionTrueFalse]
             */
            if (remaining > 0) {
                if (result_len + remaining > input_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, remaining);
                result_len += remaining;
            }
            break;
        }
    }
    
    result[result_len] = '\0';
    regfree(&regex);
    
    tmp = realloc(result, result_len + 1);
    return tmp ? tmp : result;
}

int main(void) {
    const char *test_string = "abcDEFghIJKlmnoP";
    char *cleaned = remove_uppercase_substrings(test_string);
    
    if (cleaned) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}