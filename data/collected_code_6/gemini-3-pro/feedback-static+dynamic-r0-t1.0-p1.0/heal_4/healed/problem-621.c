#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    size_t new_len = len * 2 + 1;
    char* result = (char*)malloc(new_len);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            long val = 0;
            while (i < len && isdigit((unsigned char)str[i])) {
                val = val * 10 + (str[i] - '0');
                i++;
            }
            val += k;

            int req = snprintf(NULL, 0, "%ld", val);
            if (req > 0) {
                char* num_str = (char*)malloc(req + 1);
                if (num_str != NULL) {
                    snprintf(num_str, req + 1, "%ld", val);
                    if (res_idx + req >= new_len) {
                        new_len = (res_idx + req) * 2 + 1;
                        char* temp = (char*)realloc(result, new_len);
                        if (temp == NULL) {
                            free(num_str);
                            free(result);
                            return NULL;
                        }
                        result = temp;
                    }
                    for (int j = 0; j < req; j++) {
                        result[res_idx++] = num_str[j];
                    }
                    free(num_str);
                }
            }
        } else {
            if (res_idx + 1 >= new_len) {
                new_len = new_len * 2 + 1;
                char* temp = (char*)realloc(result, new_len);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(void) {
    size_t max_size = 16384;
    char* buffer = (char*)malloc(max_size);
    if (buffer == NULL) return 1;

    size_t idx = 0;
    int ch;
    while ((ch = getchar()) != EOF && idx < max_size - 1) {
        buffer[idx++] = (char)ch;
    }
    buffer[idx] = '\0';

    int k = 0;
    size_t split_idx = idx;
    
    while (split_idx > 0 && isspace((unsigned char)buffer[split_idx - 1])) {
        split_idx--;
    }
    size_t k_end = split_idx;
    while (split_idx > 0 && (isdigit((unsigned char)buffer[split_idx - 1]) || buffer[split_idx - 1] == '-')) {
        split_idx--;
    }
    if (split_idx < k_end) {
        k = atoi(&buffer[split_idx]);
        while (split_idx > 0 && isspace((unsigned char)buffer[split_idx - 1])) {
            split_idx--;
        }
        buffer[split_idx] = '\0';
    }

    if (buffer[0] == '"' || buffer[0] == '\'') {
        char quote = buffer[0];
        size_t end_quote = split_idx - 1;
        if (end_quote > 0 && buffer[end_quote] == quote) {
            buffer[end_quote] = '\0';
            memmove(buffer, buffer + 1, end_quote);
        }
    }

    char* output = increment_numeric_values(buffer, k);
    if (output != NULL) {
        printf("['");
        
        size_t out_len = 0;
        while (output[out_len] != '\0') {
            out_len++;
        }
        
        int first = 1;
        size_t i = 0;
        while (i < out_len) {
            while (i < out_len && isspace((unsigned char)output[i])) {
                i++;
            }
            if (i >= out_len) break;
            
            if (!first) {
                printf("', '");
            }
            first = 0;
            
            while (i < out_len && !isspace((unsigned char)output[i])) {
                putchar(output[i]);
                i++;
            }
        }
        printf("']\n");
        free(output);
    }
    
    free(buffer);
    return 0;
}