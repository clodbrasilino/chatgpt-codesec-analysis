#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }
    
    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    if (input_len >= 65536) {
        regfree(&regex);
        return NULL;
    }
    
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    const char *src = input;
    char *dst = result;
    size_t dst_size = input_len + 1;
    size_t dst_used = 0;
    regmatch_t match;
    
    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;
        
        if (match_start > 0) {
            if (match_start > dst_size - dst_used - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(dst, src, match_start);
            dst += match_start;
            dst_used += match_start;
        }
        
        if (dst_used >= dst_size - 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        *dst++ = ' ';
        dst_used++;
        
        src += match_end;
    }
    
    size_t remaining = strlen(src);
    if (remaining >= dst_size - dst_used) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    memcpy(dst, src, remaining + 1);
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "Google  Assistant",
        "Quad   Core",
        "ChromeCast    Built-in"
    };
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        char *cleaned = remove_multiple_spaces(test_cases[i]);
        
        if (cleaned != NULL) {
            printf("%s\n", cleaned);
            free(cleaned);
        } else {
            fprintf(stderr, "Error processing string\n");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}