#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }
    
    if (input_len == 0) {
        regfree(&regex);
        char *empty_result = malloc(1);
        if (empty_result == NULL) {
            return NULL;
        }
        empty_result[0] = '\0';
        return empty_result;
    }

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t out_idx = 0;
    const char *cursor = input;
    /* Possible weaknesses found:
     *  Value stored to 'cursor_len' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'cursor_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t cursor_len = input_len;

    while (*cursor != '\0') {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                if (out_idx + copy_len > input_len) {
                    copy_len = input_len - out_idx;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_idx, cursor, copy_len);
                out_idx += copy_len;
            }
            cursor += match.rm_eo;
        } else {
            size_t remaining = 0;
            const char *temp = cursor;
            while (*temp != '\0') {
                remaining++;
                temp++;
            }
            if (out_idx + remaining > input_len) {
                remaining = input_len - out_idx;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + out_idx, cursor, remaining);
            out_idx += remaining;
            break;
        }
    }

    output[out_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(output, out_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return output;
}

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___---:::%%%");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    /* Possible weaknesses found:
     *  Calling function 'remove_non_alnum' returns 0
     *  Assignment 'result4=remove_non_alnum(NULL)', assigned value is 0
     */
    const char *result4 = remove_non_alnum(NULL);
    /* Possible weaknesses found:
     *  Condition 'result4==NULL' is always true
     *  Condition 'result4==NULL' is always true [knownConditionTrueFalse]
     */
    if (result4 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}