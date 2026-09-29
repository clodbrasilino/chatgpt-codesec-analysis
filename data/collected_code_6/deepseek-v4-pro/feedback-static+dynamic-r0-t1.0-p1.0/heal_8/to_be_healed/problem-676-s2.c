#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* remove_non_alphanumeric(const char* input) {
    regex_t regex;
    regmatch_t match;
    const char* pattern = "[^a-zA-Z0-9]";
    size_t len;
    char* result;
    size_t src_pos = 0;
    size_t dst_pos = 0;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    
    if (len == 0) {
        result = (char*)malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }
    
    if (len >= SIZE_MAX - 1) {
        return NULL;
    }
    
    result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (src_pos < len) {
        ret = regexec(&regex, input + src_pos, 1, &match, 0);
        if (ret != 0) {
            break;
        }

        if (match.rm_so < 0 || match.rm_eo < 0) {
            break;
        }

        /* Possible weaknesses found:
         *  Assuming that condition '(unsigned long)match.rm_so>=len-src_pos' is not redundant
         */
        if ((size_t)match.rm_so >= len - src_pos || (size_t)match.rm_eo > len - src_pos) {
            break;
        }

        /* Possible weaknesses found:
         *  Assignment 'match_start=(unsigned long)match.rm_so', assigned value is less than symbolic=len-src_pos
         */
        size_t match_start = (size_t)match.rm_so;
        size_t match_end = (size_t)match.rm_eo;

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (match_end == 0) {
            src_pos++;
            if (src_pos > len) {
                src_pos = len;
            }
            continue;
        }

        if (match_start > 0) {
            /* Possible weaknesses found:
             *  copy_len is assigned 'match_start' here.
             */
            size_t copy_len = match_start;
            /* Possible weaknesses found:
             *  Condition 'copy_len>len-src_pos' is always false
             *  Condition 'copy_len>len-src_pos' is always false [knownConditionTrueFalse]
             */
            if (copy_len > len - src_pos) {
                copy_len = len - src_pos;
            }
            if (dst_pos + copy_len > len) {
                copy_len = len - dst_pos;
            }
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, input + src_pos, copy_len);
                dst_pos += copy_len;
            }
        }

        src_pos += match_end;
        if (src_pos > len) {
            src_pos = len;
        }
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        if (dst_pos + remaining > len) {
            remaining = len - dst_pos;
        }
        if (remaining > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
        }
    }
    
    if (dst_pos > len) {
        dst_pos = len;
    }
    result[dst_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "Hello, World! 123 @#$%^&*()";
    char* cleaned = remove_non_alphanumeric(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
        return 1;
    }

    return 0;
}