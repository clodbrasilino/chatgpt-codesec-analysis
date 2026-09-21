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

    size_t out_capacity = len + 128;
    char* result = malloc(out_capacity);
    if (!result) {
        return NULL;
    }

    size_t buf_idx = 0;
    size_t i = 0;
    
    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            char* endptr;
            long long val = strtoll(input + i, &endptr, 10);
            
            size_t num_chars_read = (size_t)(endptr - (input + i));
            i += num_chars_read;
            
            val += k;
            
            int max_num_len = 32;
            if (buf_idx + max_num_len >= out_capacity) {
                out_capacity = buf_idx + max_num_len + (len - i) + 128;
                char* temp = realloc(result, out_capacity);
                if (!temp) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            
            int new_len = snprintf(result + buf_idx, out_capacity - buf_idx, "%lld", val);
            if (new_len >= 0) {
                buf_idx += new_len;
            } else {
                free(result);
                return NULL;
            }
        } else {
            if (buf_idx + 2 >= out_capacity) {
                out_capacity += 64;
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
    const char* original = "Hello 123, this is a test 45!";
    int k = 10;
    
    char* modified = increment_numeric_values(original, k);
    if (modified) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        printf("Failed to process string.\n");
    }
    
    return 0;
}