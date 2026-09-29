#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t new_len = 64;
    char* result = (char*)malloc(new_len);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            long val = 0;
            
            while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
                val = val * 10 + (str[i] - '0');
                i++;
            }
            val += k;
            
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
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
                
                size_t j = 0;
                while (j < (size_t)written) {
                    result[res_idx++] = num_str[j++];
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

    if (res_idx >= new_len) {
        char* temp = (char*)realloc(result, res_idx + 1);
        if (temp == NULL) {
            free(result);
            return NULL;
        }
        result = temp;
    }
    result[res_idx] = '\0';
    
    return result;
}

int main(void) {
    const char* input = "There are 5 apples and 12 oranges.";
    int k = 3;

    char* output = increment_numeric_values(input, k);
    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Modified: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return EXIT_SUCCESS;
}