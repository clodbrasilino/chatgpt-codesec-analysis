#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096
#define INITIAL_CAPACITY 8

static char **cleanup_and_return_null(char **result, int count, regex_t *regex) {
    if (result != NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
    }
    if (regex != NULL) {
        regfree(regex);
    }
    return NULL;
}

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    char **result = NULL;
    size_t capacity = 0;
    size_t start = 0;
    size_t i = 0;
    
    if (input == NULL || count == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(input, MAX_INPUT_LENGTH);
    if (len >= MAX_INPUT_LENGTH) {
        return NULL;
    }
    
    *count = 0;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }
    
    capacity = INITIAL_CAPACITY;
    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    while (i < len) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            size_t match_pos = i + (size_t)matches[0].rm_so;
            size_t segment_len = match_pos - start;
            
            if (segment_len > 0) {
                if (segment_len > MAX_INPUT_LENGTH) {
                    return cleanup_and_return_null(result, *count, &regex);
                }
                
                if ((size_t)(*count) >= capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity > SIZE_MAX / sizeof(char *)) {
                        return cleanup_and_return_null(result, *count, &regex);
                    }
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        return cleanup_and_return_null(result, *count, &regex);
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                
                result[*count] = malloc(segment_len + 1);
                if (result[*count] == NULL) {
                    return cleanup_and_return_null(result, *count, &regex);
                }
                
                memcpy(result[*count], input + start, segment_len);
                result[*count][segment_len] = '\0';
                (*count)++;
            }
            
            start = match_pos;
            i = match_pos + 1;
        } else {
            i++;
        }
    }
    
    if (start < len) {
        size_t segment_len = len - start;
        
        if (segment_len > MAX_INPUT_LENGTH) {
            return cleanup_and_return_null(result, *count, &regex);
        }
        
        if ((size_t)(*count) >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                return cleanup_and_return_null(result, *count, &regex);
            }
            char **temp = realloc(result, new_capacity * sizeof(char *));
            if (temp == NULL) {
                return cleanup_and_return_null(result, *count, &regex);
            }
            result = temp;
            capacity = new_capacity;
        }
        
        result[*count] = malloc(segment_len + 1);
        if (result[*count] == NULL) {
            return cleanup_and_return_null(result, *count, &regex);
        }
        
        memcpy(result[*count], input + start, segment_len);
        result[*count][segment_len] = '\0';
        (*count)++;
    }
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_uppercase(test_string, &count);
    
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);
    
    return 0;
}