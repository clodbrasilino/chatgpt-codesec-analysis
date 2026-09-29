#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        if (regexec(&regex, str + src_offset, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                memcpy(result + dest_offset, str + src_offset, match.rm_so);
                dest_offset += match.rm_so;
            }
            result[dest_offset++] = ':';
            src_offset += match.rm_eo;
        } else {
            size_t remaining = len - src_offset;
            memcpy(result + dest_offset, str + src_offset, remaining);
            dest_offset += remaining;
            src_offset += remaining;
        }
    }

    result[dest_offset] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char* input = "Hello world, this.is a test";
    char* output = replace_with_colon(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}