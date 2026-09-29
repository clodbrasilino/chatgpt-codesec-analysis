#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_with_colon(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *src = str;
    char *dst = result;
    regmatch_t match;
    size_t dst_remaining = len + 1;

    while (1) {
        ret = regexec(&regex, src, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = len - (src - str);
            if (remaining_len > dst_remaining) {
                remaining_len = dst_remaining;
            }
            for (size_t i = 0; i < remaining_len; ++i) {
                dst[i] = src[i];
            }
            dst += remaining_len;
            break;
        }
        
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t copy_len = match.rm_so;
        if (copy_len > dst_remaining) {
            copy_len = dst_remaining;
        }
        for (size_t i = 0; i < copy_len; ++i) {
            dst[i] = src[i];
        }
        dst += copy_len;
        dst_remaining -= copy_len;

        if (dst_remaining > 0) {
            *dst = ':';
            dst++;
            dst_remaining--;
        }

        src += match.rm_eo;
    }

    *dst = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char input[] = "Hello world, this.is a test.";
    char *output = replace_with_colon(input, sizeof(input) - 1);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}