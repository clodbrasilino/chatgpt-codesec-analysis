#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,\\.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    const char* p = str;
    while (*p) {
        regmatch_t match;
        if (regexec(&regex, p, 1, &match, 0) == 0) {
            size_t prefix_len = match.rm_so;
            memcpy(result + res_idx, p, prefix_len);
            res_idx += prefix_len;
            result[res_idx++] = ':';
            p += match.rm_eo;
        } else {
            size_t remaining = strlen(p);
            memcpy(result + res_idx, p, remaining);
            res_idx += remaining;
            break;
        }
    }
    result[res_idx] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char* input = "Hello world, this.is a test.";
    char* output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}