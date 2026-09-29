#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        if (len == SIZE_MAX) {
            return NULL;
        }
        len++;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,\\.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t alloc_size = len * 2 + 1;
    if (alloc_size <= len) {
        regfree(&regex);
        return NULL;
    }

    char* result = malloc(alloc_size);
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
            size_t prefix_len = match_start - src_offset;

            if (prefix_len > alloc_size - dest_offset - 1) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            if (prefix_len > 0) {
                size_t chunk_size = prefix_len < (alloc_size - dest_offset - 1) ? prefix_len : (alloc_size - dest_offset - 1);
                memcpy(result + dest_offset, str + src_offset, chunk_size);
                dest_offset += chunk_size;
                if (chunk_size != prefix_len) {
                    break;
                }
            }

            if (dest_offset >= alloc_size - 1) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            result[dest_offset++] = ':';

            src_offset = src_offset + match.rm_eo;
        } else {
            size_t remaining = len - src_offset;
            
            if (remaining > alloc_size - dest_offset - 1) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            if (remaining > 0) {
                size_t chunk_size = remaining < (alloc_size - dest_offset - 1) ? remaining : (alloc_size - dest_offset - 1);
                memcpy(result + dest_offset, str + src_offset, chunk_size);
                dest_offset += chunk_size;
                if (chunk_size != remaining) {
                    break;
                }
            }
            src_offset += remaining;
        }
    }

    if (dest_offset >= alloc_size) {
        regfree(&regex);
        free(result);
        return NULL;
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