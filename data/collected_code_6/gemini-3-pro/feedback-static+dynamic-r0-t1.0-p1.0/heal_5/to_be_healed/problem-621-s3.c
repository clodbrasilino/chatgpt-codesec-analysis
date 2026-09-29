#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t cap = 256;
    char* result = (char*)malloc(cap);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '[';
    result[1] = '\0';
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
            result[result_len++] = ',';
            result[result_len++] = ' ';
            result[result_len] = '\0';
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
            
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp[64];
            int written = snprintf(temp, sizeof(temp), "'%llu'", num + k);
            if (written > 0 && (size_t)written < sizeof(temp)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, temp, written);
                result_len += written;
                result[result_len] = '\0';
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
        } else {
            free(result);
            return NULL;
        }
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
    
    size_t len = 0;
    while (buffer[len] != '\0') {
        len++;
    }
    
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[len-1] = '\0';
        len--;
    }

    char *k_buf = NULL;
    size_t k_bufsize = 0;
    long k = 0;
    
    if (getline(&k_buf, &k_bufsize, stdin) != -1) {
        char *endptr;
        k = strtol(k_buf, &endptr, 10);
        if (k > INT_MAX) k = INT_MAX;
        if (k < INT_MIN) k = INT_MIN;
    }
    free(k_buf);

    char* new_str = increment_numeric_values(buffer, (int)k);
    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    }

    free(buffer);
    return 0;
}