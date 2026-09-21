#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t result_size = len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    size_t str_offset = 0;
    regmatch_t match;

    while (str_offset < len) {
        ret = regexec(&regex, str + str_offset, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t copy_len = len - str_offset;
            if (copy_len > 0) {
                size_t available = result_size - 1 - result_idx;
                if (copy_len > available) {
                    copy_len = available;
                }
                if (result_idx + copy_len <= result_size - 1) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_idx, str + str_offset, copy_len);
                }
                result_idx += copy_len;
            }
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t copy_len = match.rm_so;
        if (copy_len > 0) {
            size_t available = result_size - 1 - result_idx;
            if (copy_len > available) {
                copy_len = available;
            }
            if (result_idx + copy_len <= result_size - 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, str + str_offset, copy_len);
            }
            result_idx += copy_len;
        }

        str_offset += match.rm_eo;
    }

    if (result_idx < result_size) {
        result[result_idx] = '\0';
    } else {
        result[result_size - 1] = '\0';
    }

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        final_result = result;
    }

    regfree(&regex);

    return final_result;
}

int main(void) {
    const char *input = "H3ll0 W0rld! @2024 #C_Programming*()";
    char *output = remove_non_alnum(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}