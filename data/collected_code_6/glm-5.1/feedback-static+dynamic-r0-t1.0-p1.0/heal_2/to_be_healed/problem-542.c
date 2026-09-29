#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,\\.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char* result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        ret = regexec(&regex, str + src_offset, 1, &match, 0);
        if (ret == 0) {
            size_t match_start = src_offset + match.rm_so;
            size_t match_len = match.rm_eo - match.rm_so;

            size_t prefix_len = match_start - src_offset;
            size_t copy_len = prefix_len < (len - dest_offset) ? prefix_len : (len - dest_offset);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dest_offset, str + src_offset, copy_len);
            dest_offset += copy_len;

            size_t colon_len = match_len < (len - dest_offset) ? match_len : (len - dest_offset);
            for (size_t i = 0; i < colon_len; i++) {
                result[dest_offset++] = ':';
            }

            src_offset = src_offset + match.rm_eo;
        } else {
            size_t remaining = len - src_offset;
            size_t copy_len = remaining < (len - dest_offset) ? remaining : (len - dest_offset);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dest_offset, str + src_offset, copy_len);
            dest_offset += copy_len;
            src_offset += remaining;
        }
    }

    if (dest_offset > len) {
        dest_offset = len;
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