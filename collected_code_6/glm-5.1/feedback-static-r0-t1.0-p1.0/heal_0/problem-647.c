#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* str, size_t* count) {
    *count = 0;
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        char** result = malloc(sizeof(char*));
        if (result == NULL) {
            return NULL;
        }
        result[0] = calloc(1, sizeof(char));
        if (result[0] == NULL) {
            free(result);
            return NULL;
        }
        return result;
    }
    
    size_t num_upper = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            num_upper++;
        }
    }
    
    size_t num_tokens = num_upper > 0 ? num_upper : 1;
    char** result = malloc((num_tokens + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }
    
    size_t token_idx = 0;
    const char* start = str;
    
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i]) && i > 0) {
            size_t token_len = str + i - start;
            result[token_idx] = malloc(token_len + 1);
            if (result[token_idx] == NULL) {
                for (size_t j = 0; j < token_idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[token_idx], start, token_len);
            result[token_idx][token_len] = '\0';
            token_idx++;
            start = str + i;
        }
    }
    
    size_t token_len = str + len - start;
    if (token_len > 0 || token_idx == 0) {
        result[token_idx] = malloc(token_len + 1);
        if (result[token_idx] == NULL) {
            for (size_t j = 0; j < token_idx; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        memcpy(result[token_idx], start, token_len);
        result[token_idx][token_len] = '\0';
        token_idx++;
    }
    
    *count = token_idx;
    result[token_idx] = NULL;
    return result;
}

void free_split_result(char** result) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* input = "SplitThisStringAtUppercaseLetters";
    size_t count = 0;
    
    char** result = split_at_uppercase(input, &count);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", result[i]);
    }
    
    free_split_result(result);
    
    return 0;
}