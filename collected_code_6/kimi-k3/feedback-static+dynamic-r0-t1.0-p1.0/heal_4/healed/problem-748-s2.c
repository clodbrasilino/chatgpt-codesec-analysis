#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_before_capitals(const char* input, size_t input_size) {
    regex_t regex;
    regmatch_t match;
    const char* cursor;
    const char* end;
    char* result;
    size_t result_len;
    size_t result_capacity;
    int ret;
    
    if (input == NULL || input_size == 0) {
        return NULL;
    }
    
    end = memchr(input, '\0', input_size);
    if (end == NULL) {
        return NULL;
    }
    
    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }
    
    result_capacity = (size_t)(end - input) * 2 + 1;
    result = malloc(result_capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    result[0] = '\0';
    result_len = 0;
    cursor = input;
    
    while (cursor < end) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining = (size_t)(end - cursor);
            size_t needed = result_len + remaining + 1;
            
            if (needed > result_capacity) {
                char* temp = realloc(result, needed);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                result_capacity = needed;
            }
            
            memcpy(result + result_len, cursor, remaining);
            result[result_len + remaining] = '\0';
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        size_t prefix_len = match.rm_so;
        size_t needed = result_len + prefix_len + 2;
        
        if (needed > result_capacity) {
            char* temp = realloc(result, needed * 2);
            if (temp == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            result_capacity = needed * 2;
        }
        
        memcpy(result + result_len, cursor, prefix_len);
        result_len += prefix_len;
        
        if (result_len > 0) {
            result[result_len++] = ' ';
        }
        
        result[result_len++] = cursor[match.rm_so];
        result[result_len] = '\0';
        
        cursor += match.rm_eo;
    }
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "HelloWorldThisIsATest";
    char* result;
    size_t test_len;
    
    test_len = strlen(test_string);
    result = add_spaces_before_capitals(test_string, test_len + 1);
    
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", result);
    
    free(result);
    
    return EXIT_SUCCESS;
}