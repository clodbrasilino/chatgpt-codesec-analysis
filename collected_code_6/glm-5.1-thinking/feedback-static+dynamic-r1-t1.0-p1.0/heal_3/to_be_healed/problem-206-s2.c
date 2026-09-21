#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 1048576

char **concat_adjacent(const char **tuple, size_t len, size_t *out_len) {
    if (tuple == NULL || out_len == NULL) {
        return NULL;
    }
    if (len % 2 != 0) {
        return NULL;
    }
    
    size_t res_len = len / 2;
    if (res_len == 0) {
        *out_len = 0;
        return NULL;
    }
    
    if (res_len > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }
    
    char **result = malloc(res_len * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < res_len; i++) {
        const char *s1 = tuple[i * 2];
        const char *s2 = tuple[i * 2 + 1];
        
        if (s1 == NULL || s2 == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        size_t l1 = strnlen(s1, MAX_STR_LEN);
        size_t l2 = strnlen(s2, MAX_STR_LEN);
        
        if (l1 > SIZE_MAX - l2) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        size_t total = l1 + l2;
        
        if (total > SIZE_MAX - 1) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        result[i] = malloc(total + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], s1, l1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + l1, s2, l2);
        result[i][total] = '\0';
    }
    
    *out_len = res_len;
    return result;
}

void free_concat_result(char **result, size_t len) {
    if (result != NULL) {
        for (size_t i = 0; i < len; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char *input[] = {"Hello", "World", "Foo", "Bar"};
    size_t input_len = sizeof(input) / sizeof(input[0]);
    size_t out_len = 0;
    
    char **result = concat_adjacent(input, input_len, &out_len);
    
    if (result != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("%s\n", result[i]);
        }
        free_concat_result(result, out_len);
    }
    
    return 0;
}