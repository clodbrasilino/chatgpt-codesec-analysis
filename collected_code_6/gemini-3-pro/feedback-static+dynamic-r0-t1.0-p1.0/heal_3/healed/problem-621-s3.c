#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t cap = 256;
    char* result = (char*)malloc(cap);
    if (result == NULL) {
        return NULL;
    }
    
    strcpy(result, "[");
    size_t result_len = 1;
    
    const char* p = input;
    int first = 1;
    
    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }
        
        const char* start = p;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }
        
        int is_num = 1;
        for (const char* q = start; q < p; q++) {
            if (!isdigit((unsigned char)*q)) {
                is_num = 0;
                break;
            }
        }
        
        size_t token_len = (size_t)(p - start);
        size_t max_req = result_len + token_len + 64; 
        if (max_req > cap) {
            cap = max_req * 2;
            char* new_result = (char*)realloc(result, cap);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
        }
        
        if (!first) {
            strcpy(result + result_len, ", ");
            result_len += 2;
        } else {
            first = 0;
        }
        
        if (is_num) {
            unsigned long long num = 0;
            for (const char* q = start; q < p; q++) {
                if (num <= (18446744073709551615ULL - 9) / 10) {
                    num = num * 10 + (*q - '0');
                }
            }
            
            char temp[64];
            int written = snprintf(temp, sizeof(temp), "'%llu'", num + k);
            if (written > 0) {
                strcpy(result + result_len, temp);
                result_len += written;
            }
        } else {
            result[result_len++] = '\'';
            for (const char* q = start; q < p; q++) {
                result[result_len++] = *q;
            }
            result[result_len++] = '\'';
            result[result_len] = '\0';
        }
    }
    
    if (result_len + 2 > cap) {
        cap = result_len + 2;
        char* new_result = (char*)realloc(result, cap);
        if (new_result != NULL) {
            result = new_result;
        }
    }
    
    strcpy(result + result_len, "]");
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
        buffer[len-1] = '\0';
        len--;
    }

    char k_buf[64];
    int k = 0;
    if (fgets(k_buf, sizeof(k_buf), stdin) != NULL) {
        k = atoi(k_buf);
    }

    char* new_str = increment_numeric_values(buffer, k);
    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    }

    free(buffer);
    return 0;
}