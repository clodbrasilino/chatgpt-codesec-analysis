#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_with_colon(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *src = str;
    char *dst = result;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, src, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t src_offset = (size_t)(src - str);
            size_t remaining_len = len - src_offset;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, remaining_len);
            dst[remaining_len] = '\0';
            break;
        }
        
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t src_offset = (size_t)(src - str);
        size_t remaining_len = len - src_offset;
        size_t copy_len = (size_t)match.rm_so;

        if (copy_len > remaining_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src, copy_len);
        dst += copy_len;
        *dst = ':';
        dst++;
        src += match.rm_eo;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = "Hello world, this.is a test.";
    char *output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}