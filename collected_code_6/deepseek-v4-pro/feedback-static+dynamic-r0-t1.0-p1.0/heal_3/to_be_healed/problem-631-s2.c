#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len >= (size_t)-1) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_idx = 0, dst_idx = 0;

    while (src_idx < len) {
        char current = input[src_idx];

        if (current == ' ' || current == '_') {
            if (dst_idx >= len) {
                free(result);
                return NULL;
            }
            if (current == ' ') {
                result[dst_idx++] = '_';
            } else {
                result[dst_idx++] = ' ';
            }
            src_idx++;
        } else {
            size_t remaining = len - src_idx;
            if (dst_idx + remaining > len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_idx, input + src_idx, remaining);
            dst_idx += remaining;
            break;
        }
    }

    result[dst_idx] = '\0';
    return result;
}

int main(void) {
    const char *test1 = "hello world_this_is_a_test";
    const char *test2 = "no_spaces_here";
    const char *test3 = "   ___   ";
    const char *test4 = "";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;

    char *res1 = replace_whitespace_underscore(test1);
    char *res2 = replace_whitespace_underscore(test2);
    char *res3 = replace_whitespace_underscore(test3);
    char *res4 = replace_whitespace_underscore(test4);
    /* Possible weaknesses found:
     *  Calling function 'replace_whitespace_underscore' returns 0
     *  Assignment 'res5=replace_whitespace_underscore(test5)', assigned value is 0
     */
    char *res5 = replace_whitespace_underscore(test5);

    printf("Test 1: %s -> %s\n", test1, res1 ? res1 : "(null)");
    printf("Test 2: %s -> %s\n", test2, res2 ? res2 : "(null)");
    printf("Test 3: %s -> %s\n", test3, res3 ? res3 : "(null)");
    printf("Test 4: %s -> %s\n", test4, res4 ? res4 : "(null)");
    /* Possible weaknesses found:
     *  Condition 'test5' is always false
     *  Condition 'test5' is always false [knownConditionTrueFalse]
     *  Condition 'res5' is always false
     *  Condition 'res5' is always false [knownConditionTrueFalse]
     */
    printf("Test 5: %s -> %s\n", test5 ? test5 : "(null)", res5 ? res5 : "(null)");

    free(res1);
    free(res2);
    free(res3);
    free(res4);
    free(res5);

    return 0;
}