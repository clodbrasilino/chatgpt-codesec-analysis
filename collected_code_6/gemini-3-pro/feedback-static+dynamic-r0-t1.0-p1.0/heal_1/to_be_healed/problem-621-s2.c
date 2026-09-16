#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (!input) {
        return NULL;
    }

    size_t len = strlen(input);
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
            strncpy(num_str, input + start, num_len);
            num_str[num_len] = '\0';
            
            long long val = strtoll(num_str, NULL, 10);
            free(num_str);
            
            val += k;
            
            char new_num_str[64];
            int new_len = snprintf(new_num_str, sizeof(new_num_str), "%lld", val);
            if (new_len < 0) {
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
            
            strcpy(result + buf_idx, new_num_str);
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