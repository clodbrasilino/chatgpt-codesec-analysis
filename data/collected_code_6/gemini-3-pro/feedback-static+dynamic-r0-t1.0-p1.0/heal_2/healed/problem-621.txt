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

            char num_str[64];
            int written = snprintf(num_str, sizeof(num_str), "%ld", val);
            if (written > 0 && (size_t)written < sizeof(num_str)) {
                if (res_idx + written >= new_len) {
                    new_len = (res_idx + written) * 2 + 1;
                    char* temp = (char*)realloc(result, new_len);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                for (int j = 0; j < written; j++) {
                    result[res_idx++] = num_str[j];
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
    char buffer[4096];
    int k;

    if (scanf("%d ", &k) == 1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = 0;
            while (buffer[len] != '\0') {
                len++;
            }
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            
            char* output = increment_numeric_values(buffer, k);
            if (output != NULL) {
                printf("['");
                size_t out_len = 0;
                while (output[out_len] != '\0') out_len++;
                
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
        }
    }

    return 0;
}