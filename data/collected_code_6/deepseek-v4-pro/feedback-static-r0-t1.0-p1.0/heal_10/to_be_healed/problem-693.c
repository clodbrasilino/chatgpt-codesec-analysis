#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    
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
    size_t dst_capacity = len + 1;
    size_t dst_used = 0;
    regmatch_t match;
    int exec_flags = 0;

    while (regexec(&regex, src, 1, &match, exec_flags) == 0) {
        exec_flags = REG_NOTBOL;
        
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            size_t available = dst_capacity - dst_used;
            /* Possible weaknesses found:
             *  Assuming that condition 'match_start>available' is not redundant
             */
            if (match_start > available) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            
            /* Possible weaknesses found:
             *  Condition 'available>=match_start' is always true [knownConditionTrueFalse]
             *  Condition 'available>=match_start' is always true
             */
            if (available >= match_start) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dst, src, match_start);
                dst += match_start;
                dst_used += match_start;
            }
        }

        size_t available = dst_capacity - dst_used;
        if (available < 2) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        *dst++ = ' ';
        dst_used++;

        src += match_end;
    }

    size_t remaining = strnlen(src, SIZE_MAX);
    size_t available = dst_capacity - dst_used;

    /* Possible weaknesses found:
     *  Assuming that condition 'remaining+1>available' is not redundant
     */
    if (remaining + 1 > available) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'available>=remaining+1' is always true
     *  Condition 'available>=remaining+1' is always true [knownConditionTrueFalse]
     */
    if (available >= remaining + 1) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src, remaining + 1);
    } else {
        free(result);
        regfree(&regex);
        return NULL;
    }

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