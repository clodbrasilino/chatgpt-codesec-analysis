#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char* cursor = str;
    const char* end = str + len;

    while (cursor < end) {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            if (match.rm_so > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_idx, cursor, match.rm_so);
                result_idx += match.rm_so;
            }
            cursor += match.rm_eo;
        } else {
            size_t remaining = end - cursor;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, cursor, remaining);
            result_idx += remaining;
            break;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);

    char* shrunk = (char*)realloc(result, result_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
    
    return result;
}

int main(void) {
    const char* input = "Hello World 123 test CASE";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* output = remove_lowercase_substrings(input, len);
    
    if (output != NULL) {
        printf("Input:  %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to process string.\n");
        return 1;
    }
    
    return 0;
}