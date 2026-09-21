#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        char* empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,\\.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t bufsize = len * 2 + 1;
    char* result = malloc(bufsize);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = str;
    size_t offset = 0;

    while (*p) {
        regmatch_t match;
        if (regexec(&regex, p, 1, &match, 0) != 0) {
            break;
        }

        size_t prefix_len = match.rm_so;
        
        size_t needed = offset + prefix_len + 1;
        if (bufsize < needed) {
            size_t new_bufsize = bufsize + (needed - bufsize);
            char* new_result = realloc(result, new_bufsize);
            if (new_result == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
            bufsize = new_bufsize;
        }

        if (prefix_len > 0) {
            memcpy(result + offset, p, prefix_len);
        }
        offset += prefix_len;
        
        if (bufsize < offset + 1) {
            size_t new_bufsize = bufsize + 1;
            char* new_result = realloc(result, new_bufsize);
            if (new_result == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
            bufsize = new_bufsize;
        }
        result[offset++] = ':';
        p += match.rm_eo;
    }

    size_t remaining = strnlen(p, (str + len) - p);
    size_t final_needed = offset + remaining + 1;
    if (bufsize < final_needed) {
        size_t new_bufsize = bufsize + (final_needed - bufsize);
        char* new_result = realloc(result, new_bufsize);
        if (new_result == NULL) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = new_result;
        bufsize = new_bufsize;
    }

    if (remaining > 0) {
        memcpy(result + offset, p, remaining);
    }
    offset += remaining;
    result[offset] = '\0';

    regfree(&regex);
    return result;
}

int main(int argc, char* argv[]) {
    const char* input = "Hello world, this.is a test";
    
    char* output = replace_with_colon(input);
    if (output == NULL) {
        fprintf(stderr, "Regex replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    return EXIT_SUCCESS;
}