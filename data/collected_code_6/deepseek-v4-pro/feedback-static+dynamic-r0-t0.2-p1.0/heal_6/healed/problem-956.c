#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static int is_null_terminated(const char *str, size_t max_len) {
    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return 1;
        }
    }
    return 0;
}

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    char **result = NULL;
    size_t capacity = 0;
    size_t start = 0;
    size_t i = 0;
    size_t len;
    size_t safe_max = 4096;
    
    if (input == NULL || count == NULL) {
        return NULL;
    }
    
    if (!is_null_terminated(input, safe_max)) {
        return NULL;
    }
    
    len = strnlen(input, safe_max);
    if (len == safe_max) {
        return NULL;
    }
    
    *count = 0;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }
    
    result = malloc(sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    capacity = 1;
    
    while (i < len) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            size_t match_pos = i + (size_t)matches[0].rm_so;
            
            if (match_pos > start || (match_pos == start && match_pos == 0)) {
                size_t segment_len = match_pos - start;
                
                if (segment_len > 0) {
                    if ((size_t)*count >= capacity) {
                        size_t new_capacity;
                        if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                            for (size_t j = 0; j < (size_t)*count; j++) {
                                free(result[j]);
                            }
                            free(result);
                            regfree(&regex);
                            return NULL;
                        }
                        new_capacity = capacity * 2;
                        char **temp = realloc(result, new_capacity * sizeof(char *));
                        if (temp == NULL) {
                            for (size_t j = 0; j < (size_t)*count; j++) {
                                free(result[j]);
                            }
                            free(result);
                            regfree(&regex);
                            return NULL;
                        }
                        result = temp;
                        capacity = new_capacity;
                    }
                    
                    if (start + segment_len <= len) {
                        result[*count] = malloc(segment_len + 1);
                        if (result[*count] == NULL) {
                            for (size_t j = 0; j < (size_t)*count; j++) {
                                free(result[j]);
                            }
                            free(result);
                            regfree(&regex);
                            return NULL;
                        }
                        memcpy(result[*count], input + start, segment_len);
                        result[*count][segment_len] = '\0';
                        (*count)++;
                    } else {
                        for (size_t j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                }
            }
            
            start = match_pos;
            i = match_pos + 1;
        } else {
            i++;
        }
    }
    
    if (start < len) {
        size_t segment_len = len - start;
        
        if (segment_len > 0) {
            if ((size_t)*count >= capacity) {
                size_t new_capacity;
                if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                    for (size_t j = 0; j < (size_t)*count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                new_capacity = capacity * 2;
                char **temp = realloc(result, new_capacity * sizeof(char *));
                if (temp == NULL) {
                    for (size_t j = 0; j < (size_t)*count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }
            
            result[*count] = malloc(segment_len + 1);
            if (result[*count] == NULL) {
                for (size_t j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result[*count], input + start, segment_len);
            result[*count][segment_len] = '\0';
            (*count)++;
        }
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