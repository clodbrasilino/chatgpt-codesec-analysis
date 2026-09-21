#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* input, int k) {
    if (!input) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    size_t out_capacity = len + 1;
    char* result = malloc(out_capacity);
    if (!result) {
        return NULL;
    }

    size_t buf_idx = 0;
    size_t i = 0;
    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)input[i])) {
                i++;
            }
            
            size_t num_len = i - start;
            char* num_str = malloc(num_len + 1);
            if (!num_str) {
                free(result);
                return NULL;
            }
            
            for (size_t j = 0; j < num_len; j++) {
                num_str[j] = input[start + j];
            }
            num_str[num_len] = '\0';
            
            long long val = strtoll(num_str, NULL, 10);
            free(num_str);
            
            val += k;
            
            char new_num_str[128];
            int new_len = snprintf(new_num_str, sizeof(new_num_str), "%lld", val);
            if (new_len < 0 || new_len >= (int)sizeof(new_num_str)) {
                free(result);
                return NULL;
            }
            
            if (buf_idx + new_len >= out_capacity) {
                out_capacity = buf_idx + new_len + (len - i) + 1;
                char* temp = realloc(result, out_capacity);
                if (!temp) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            
            for (int j = 0; j < new_len; j++) {
                result[buf_idx + j] = new_num_str[j];
            }
            buf_idx += new_len;
        } else {
            if (buf_idx + 1 >= out_capacity) {
                out_capacity += 16;
                char* temp = realloc(result, out_capacity);
                if (!temp) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[buf_idx++] = input[i++];
        }
    }
    
    result[buf_idx] = '\0';
    return result;
}

int main(void) {
    return 0;
}