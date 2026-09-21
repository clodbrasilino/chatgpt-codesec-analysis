#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    regmatch_t match;

    while (i < len) {
        ret = regexec(&regex, str + i, 1, &match, 0);
        if (ret == 0) {
            size_t start = i + match.rm_so;
            size_t end = i + match.rm_eo;
            size_t copy_len = start - i;

            if (j + copy_len <= len) {
                if (len + 1 - j >= copy_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + j, str + i, copy_len);
                    j += copy_len;
                }
            }

            if (j + 1 <= len) {
                result[j++] = ':';
            }

            i = end;
        } else {
            size_t copy_len = len - i;

            if (j + copy_len <= len) {
                if (len + 1 - j >= copy_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + j, str + i, copy_len);
                    j += copy_len;
                    i = len;
                }
            }
        }
    }

    result[j] = '\0';
    
    regfree(&regex);

    return result;
}

int main(void) {
    const char* input = "This is a test, with spaces, commas. and dots.";
    char* output = replace_with_colon(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}