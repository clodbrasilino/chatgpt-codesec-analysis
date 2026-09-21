#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_chars(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    size_t max_result_len = len * 2 + 1;
    
    if (max_result_len < len) {
        regfree(&regex);
        return NULL;
    }
    
    char *result = malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < len && dst_pos < max_result_len - 1) {
        ret = regexec(&regex, input + src_pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = len - src_pos;
            if (dst_pos + remaining >= max_result_len) {
                remaining = max_result_len - dst_pos - 1;
            }
            if (remaining > 0 && dst_pos + remaining <= max_result_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, input + src_pos, remaining);
                dst_pos += remaining;
            }
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            size_t copy_len = match_start - src_pos;
            if (dst_pos + copy_len >= max_result_len) {
                copy_len = max_result_len - dst_pos - 1;
            }
            if (copy_len > 0 && dst_pos + copy_len <= max_result_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + dst_pos, input + src_pos, copy_len);
                dst_pos += copy_len;
            }
        }

        if (dst_pos < max_result_len - 1) {
            result[dst_pos++] = ':';
        }
        src_pos = match_end;
    }

    if (dst_pos < max_result_len) {
        result[dst_pos] = '\0';
    } else if (max_result_len > 0) {
        result[max_result_len - 1] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "Hello, world. This is a test";
    char *result = replace_chars(test_str);
    
    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    return 0;
}