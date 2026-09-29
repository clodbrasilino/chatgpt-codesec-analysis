#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str) {
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t length = strnlen(str, SIZE_MAX);
    
    char* result = (char*)malloc(length + 1);
    if (!result) {
        regfree(&regex);
        return NULL;
    }
    
    size_t result_idx = 0;
    size_t str_idx = 0;
    
    while (str_idx < length) {
        regmatch_t match;
        ret = regexec(&regex, str + str_idx, 1, &match, 0);
        
        if (ret == 0) {
            size_t copy_len = match.rm_so;
            if (copy_len > 0) {
                if (result_idx + copy_len <= length) {
                    memcpy(result + result_idx, str + str_idx, copy_len);
                    result_idx += copy_len;
                }
            }
            str_idx += match.rm_eo;
        } else {
            size_t remaining = length - str_idx;
            if (result_idx + remaining <= length) {
                memcpy(result + result_idx, str + str_idx, remaining);
                result_idx += remaining;
            }
            break;
        }
    }
    
    result[result_idx] = '\0';
    
    char* trimmed = (char*)realloc(result, result_idx + 1);
    if (trimmed) {
        result = trimmed;
    }
    
    regfree(&regex);
    
    return result;
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    char* processed = remove_lowercase_substrings(argv[1]);
    if (!processed) {
        fprintf(stderr, "Memory allocation or regex compilation failed\n");
        return 1;
    }
    
    printf("%s\n", processed);
    
    free(processed);
    
    return 0;
}