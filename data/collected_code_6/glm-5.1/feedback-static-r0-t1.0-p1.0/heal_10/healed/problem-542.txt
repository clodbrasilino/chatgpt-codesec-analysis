#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }

    if (len == 0) {
        char* result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,\\.]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    regmatch_t match;
    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        ret = regexec(&regex, str + src_offset, 1, &match, 0);
        if (ret == 0) {
            size_t match_start = src_offset + match.rm_so;
            size_t prefix_len = match_start - src_offset;
            size_t match_len = match.rm_eo - match.rm_so;

            if (dest_offset + prefix_len > len) {
                break;
            }
            memcpy(result + dest_offset, str + src_offset, prefix_len);
            dest_offset += prefix_len;

            if (dest_offset + match_len > len) {
                break;
            }
            for (size_t i = 0; i < match_len; i++) {
                if (dest_offset >= len) {
                    break;
                }
                result[dest_offset++] = ':';
            }

            src_offset += match.rm_eo;
        } else {
            size_t remaining = len - src_offset;
            if (dest_offset + remaining > len) {
                break;
            }
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
    const char* original = "Hello world, this.is a test.";
    char* replaced = replace_with_colon(original);

    if (replaced != NULL) {
        printf("%s\n", replaced);
        free(replaced);
    }

    return 0;
}