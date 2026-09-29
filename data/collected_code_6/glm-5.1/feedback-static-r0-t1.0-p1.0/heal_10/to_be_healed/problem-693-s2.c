#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = 0;
    while (str[input_len] != '\0') {
        input_len++;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = str;
    size_t result_index = 0;
    size_t max_len = input_len + 1;

    while (*cursor != '\0') {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = match.rm_so;
                if (copy_len > max_len - result_index - 1) {
                    copy_len = max_len - result_index - 1;
                }
                if (copy_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_index, cursor, copy_len);
                    result_index += copy_len;
                }
            }

            if (result_index < max_len - 1) {
                result[result_index++] = ' ';
            }

            cursor += match.rm_eo;
        } else {
            size_t remaining = 0;
            while (cursor[remaining] != '\0') {
                remaining++;
            }
            size_t copy_len = remaining;
            if (copy_len > max_len - result_index - 1) {
                copy_len = max_len - result_index - 1;
            }
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_index, cursor, copy_len);
                result_index += copy_len;
            }
            break;
        }
    }

    result[result_index] = '\0';
    regfree(&regex);

    char *shrunk_result = (char *)realloc(result, result_index + 1);
    if (shrunk_result != NULL) {
        return shrunk_result;
    }
    
    return result;
}

int main(void) {
    const char *input = "This   is   a  test   string.";
    char *output = remove_multiple_spaces(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}