#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) return NULL;
    size_t cap = 256;
    char* result = (char*)malloc(cap);
    if (!result) return NULL;
    
    result[0] = '[';
    result[1] = '\0';
    size_t result_len = 1;
    
    const char* p = input;
    int first = 1;
    
    while (*p) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (!*p) break;
        
        const char* start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        
        int is_num = 1;
        for (const char* q = start; q < p; q++) {
            if (!isdigit((unsigned char)*q)) {
                is_num = 0;
                break;
            }
        }
        
        size_t token_len = (size_t)(p - start);
        size_t max_req = result_len + token_len + 128; 
        if (max_req > cap) {
            cap = max_req * 2;
            char* new_result = (char*)realloc(result, cap);
            if (!new_result) {
                free(result);
                return NULL;
            }
            result = new_result;
        }
        
        if (!first) {
            result[result_len++] = ',';
            result[result_len++] = ' ';
        } else {
            first = 0;
        }
        
        if (is_num) {
            unsigned long long num = 0;
            for (const char* q = start; q < p; q++) {
                num = num * 10 + (*q - '0');
            }
            int written = snprintf(result + result_len, cap - result_len, "'%llu'", num + k);
            if (written > 0) result_len += written;
        } else {
            result[result_len++] = '\'';
            for (const char* q = start; q < p; q++) {
                result[result_len++] = *q;
            }
            result[result_len++] = '\'';
        }
        result[result_len] = '\0';
    }
    
    if (result_len + 2 > cap) {
        char *new_result = (char*)realloc(result, result_len + 2);
        if (new_result) result = new_result;
    }
    result[result_len++] = ']';
    result[result_len] = '\0';
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    
    if (getline(&buffer, &bufsize, stdin) == -1) {
        free(buffer);
        return 0;
    }
    
    size_t len = strlen(buffer);
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[--len] = '\0';
    }

    char *k_buf = NULL;
    size_t k_bufsize = 0;
    long k = 0;
    
    if (getline(&k_buf, &k_bufsize, stdin) != -1) {
        k = strtol(k_buf, NULL, 10);
    }
    free(k_buf);

    char* new_str = increment_numeric_values(buffer, (int)k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }

    free(buffer);
    return 0;
}