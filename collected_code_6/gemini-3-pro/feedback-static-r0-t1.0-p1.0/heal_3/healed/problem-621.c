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
            
            int written = snprintf(NULL, 0, "%ld", val);
            if (written > 0) {
                if (res_idx + written >= new_len) {
                    new_len = (res_idx + written) * 2 + 1;
                    char* temp = (char*)realloc(result, new_len);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                
                snprintf(result + res_idx, new_len - res_idx, "%ld", val);
                res_idx += written;
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