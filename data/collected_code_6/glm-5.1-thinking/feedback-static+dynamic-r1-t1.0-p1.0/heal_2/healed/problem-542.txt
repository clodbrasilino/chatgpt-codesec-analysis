#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *replace_with_colon(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    size_t result_size = len + 1;
    char *result = malloc(result_size);
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
            size_t dst_offset = (size_t)(dst - result);
            if (remaining_len >= result_size - dst_offset) {
                free(result);
                regfree(&regex);
                return NULL;
            }
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

        size_t dst_offset = (size_t)(dst - result);
        if (copy_len >= result_size - dst_offset) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        memcpy(dst, src, copy_len);
        dst += copy_len;
        
        dst_offset = (size_t)(dst - result);
        if (1 >= result_size - dst_offset) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
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