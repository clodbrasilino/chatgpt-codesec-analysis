#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* input, int k) {
    if (!input) return NULL;
    size_t cap = 10000;
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
        
        if (!first) {
            strcat(result, ", ");
            result_len += 2;
        } else {
            first = 0;
        }
        
        if (is_num) {
            long long num = 0;
            for (const char* q = start; q < p; q++) {
                num = num * 10 + (*q - '0');
            }
            char buf[128];
            snprintf(buf, sizeof(buf), "'%lld'", num + k);
            strcat(result, buf);
            result_len += strlen(buf);
        } else {
            result[result_len++] = '\'';
            for (const char* q = start; q < p; q++) {
                result[result_len++] = *q;
            }
            result[result_len++] = '\'';
            result[result_len] = '\0';
        }
    }
    strcat(result, "]");
    return result;
}

int main(void) {
    char buffer[8192];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;
    }
    
    size_t len = 0;
    while (buffer[len] != '\0') {
        len++;
    }
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[--len] = '\0';
    }

    char k_buf[256];
    long k = 0;
    if (fgets(k_buf, sizeof(k_buf), stdin)) {
        k = strtol(k_buf, NULL, 10);
    }

    char* new_str = increment_numeric_values(buffer, (int)k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }

    return 0;
}