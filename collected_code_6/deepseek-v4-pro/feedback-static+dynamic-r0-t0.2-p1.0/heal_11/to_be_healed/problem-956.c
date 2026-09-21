#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_null_terminated(const char *str, size_t max_len) {
    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return 1;
        }
    }
    return 0;
}

char **split_at_uppercase(const char *input, int *count) {
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
    
    result = malloc(sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    capacity = 1;
    
    while (i < len) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            size_t match_pos = i;
            
            if (match_pos > start) {
                size_t segment_len = match_pos - start;
                
                if ((size_t)*count >= capacity) {
                    if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                        for (size_t j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    size_t new_capacity = capacity * 2;
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (size_t j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                
                if (segment_len > SIZE_MAX - 1) {
                    for (size_t j = 0; j < (size_t)*count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                result[*count] = malloc(segment_len + 1);
                if (result[*count] == NULL) {
                    for (size_t j = 0; j < (size_t)*count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                if (segment_len > 0) {
                    if (segment_len > SIZE_MAX) {
                        free(result[*count]);
                        for (size_t j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[*count], input + start, segment_len);
                }
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
        
        if ((size_t)*count >= capacity) {
            if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                for (size_t j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            char **temp = realloc(result, new_capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            result = temp;
            /* Possible weaknesses found:
             *  Value stored to 'capacity' is never read [deadcode.DeadStores]
             *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
             */
            capacity = new_capacity;
        }
        
        if (segment_len > SIZE_MAX - 1) {
            for (size_t j = 0; j < (size_t)*count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        result[*count] = malloc(segment_len + 1);
        if (result[*count] == NULL) {
            for (size_t j = 0; j < (size_t)*count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        if (segment_len > 0) {
            if (segment_len > SIZE_MAX) {
                free(result[*count]);
                for (size_t j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count], input + start, segment_len);
        }
        result[*count][segment_len] = '\0';
        (*count)++;
    }
    
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