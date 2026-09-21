#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    if (input_len == 0) {
        output[0] = '\0';
        return output;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex_t'
     *  unknown type name 'regex_t'
     */
    regex_t regex;
    /* Possible weaknesses found:
     *  implicit declaration of function 'regcomp' [-Wimplicit-function-declaration]
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'regex'
     *  'REG_EXTENDED' undeclared (first use in this function)
     *  use of undeclared identifier 'REG_EXTENDED'
     *  call to undeclared function 'regcomp'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(output);
        return NULL;
    }

    size_t out_idx = 0;
    const char *cursor = input;

    while (*cursor != '\0') {
        /* Possible weaknesses found:
         *  unknown type name 'regmatch_t'
         *  use of undeclared identifier 'regmatch_t'
         */
        regmatch_t match;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'regex'
         *  use of undeclared identifier 'match'
         *  implicit declaration of function 'regexec' [-Wimplicit-function-declaration]
         *  call to undeclared function 'regexec'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            /* Possible weaknesses found:
             *  request for member 'rm_so' in something not a structure or union
             *  use of undeclared identifier 'match'
             */
            if (match.rm_so > 0) {
                /* Possible weaknesses found:
                 *  request for member 'rm_so' in something not a structure or union
                 *  use of undeclared identifier 'match'
                 */
                size_t copy_len = match.rm_so;
                if (out_idx + copy_len <= input_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(output + out_idx, cursor, copy_len);
                    out_idx += copy_len;
                }
            }
            /* Possible weaknesses found:
             *  request for member 'rm_eo' in something not a structure or union
             *  use of undeclared identifier 'match'
             */
            if (match.rm_eo == 0) {
                cursor++;
            } else {
                /* Possible weaknesses found:
                 *  request for member 'rm_eo' in something not a structure or union
                 *  use of undeclared identifier 'match'
                 */
                cursor += match.rm_eo;
            }
        } else {
            const char *temp_cursor = cursor;
            size_t remaining = 0;
            while (*temp_cursor != '\0') {
                remaining++;
                temp_cursor++;
            }
            size_t copy_len = remaining;
            if (out_idx + copy_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_idx, cursor, copy_len);
                out_idx += copy_len;
            }
            break;
        }
    }

    output[out_idx] = '\0';
    /* Possible weaknesses found:
     *  use of undeclared identifier 'regex'
     *  implicit declaration of function 'regfree'; did you mean 'free'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'regfree'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
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
    char *result4 = remove_non_alnum(NULL);
    /* Possible weaknesses found:
     *  Condition 'result4==NULL' is always true
     *  Condition 'result4==NULL' is always true [knownConditionTrueFalse]
     */
    if (result4 == NULL) {
        printf("NULL input handled\n");
    } else {
        free(result4);
    }

    return 0;
}