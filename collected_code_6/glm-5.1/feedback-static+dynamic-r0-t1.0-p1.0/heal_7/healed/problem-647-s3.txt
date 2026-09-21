#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char** split_at_uppercase(const char* str, size_t* count) {
    if (!str) {
        *count = 0;
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    size_t capacity = 10;
    size_t idx = 0;
    
    char** result = malloc(capacity * sizeof(char*));
    if (!result) {
        return NULL;
    }
    
    const char* start = str;
    
    for (size_t i = 0; i <= len; i++) {
        if (i == len || isupper((unsigned char)str[i])) {
            if (start != str + i) {
                size_t token_len = str + i - start;
                char* token = malloc(token_len + 1);
                if (!token) {
                    for (size_t j = 0; j < idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                if (token_len > 0) {
                    size_t safe_len = token_len < token_len + 1 ? token_len : token_len + 1;
                    memcpy(token, start, safe_len);
                }
                token[token_len] = '\0';
                
                if (idx == capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        new_capacity = SIZE_MAX;
                    }
                    char** temp = realloc(result, new_capacity * sizeof(char*));
                    if (!temp) {
                        free(token);
                        for (size_t j = 0; j < idx; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }
                result[idx++] = token;
            }
            start = str + i;
        }
    }
    
    char** final_result = realloc(result, (idx + 1) * sizeof(char*));
    if (!final_result) {
        for (size_t j = 0; j < idx; j++) {
            free(result[j]);
        }
        free(result);
        return NULL;
    }
    result = final_result;
    result[idx] = NULL;
    
    *count = idx;
    return result;
}

void free_split_result(char** result) {
    if (result) {
        for (size_t i = 0; result[i] != NULL; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char* input = "SplitThisStringAtUppercaseLetters";
    size_t count = 0;
    
    char** parts = split_at_uppercase(input, &count);
    if (!parts) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
    }
    
    free_split_result(parts);
    
    return 0;
}