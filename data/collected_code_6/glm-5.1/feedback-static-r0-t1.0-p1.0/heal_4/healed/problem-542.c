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
    size_t remaining_capacity = len;

    while (src_offset < len) {
        ret = regexec(&regex, str + src_offset, 1, &match, 0);
        if (ret == 0) {
            size_t match_start = src_offset + match.rm_so;
            size_t match_len = match.rm_eo - match.rm_so;
            size_t prefix_len = match_start - src_offset;

            if (prefix_len > remaining_capacity) {
                break;
            }
            size_t chunk_size = prefix_len < remaining_capacity ? prefix_len : remaining_capacity;
            memcpy(result + dest_offset, str + src_offset, chunk_size);
            dest_offset += chunk_size;
            remaining_capacity -= chunk_size;

            if (match_len > remaining_capacity) {
                break;
            }
            size_t replace_len = match_len < remaining_capacity ? match_len : remaining_capacity;
            for (size_t i = 0; i < replace_len; i++) {
                result[dest_offset++] = ':';
            }
            remaining_capacity -= replace_len;

            src_offset = src_offset + match.rm_eo;
        } else {
            size_t remaining = len - src_offset;
            if (remaining > remaining_capacity) {
                break;
            }
            size_t chunk_size = remaining < remaining_capacity ? remaining : remaining_capacity;
            memcpy(result + dest_offset, str + src_offset, chunk_size);
            dest_offset += chunk_size;
            remaining_capacity -= chunk_size;
            src_offset += chunk_size;
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