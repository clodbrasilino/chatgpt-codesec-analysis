#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    size_t out_len = len * 2 + 1;
    char* result = (char*)malloc(out_len);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            long long num = 0;
            while (i < len && isdigit((unsigned char)input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            
            num += k;
            
            size_t temp_size = 64;
            char* temp = (char*)malloc(temp_size);
            if (temp == NULL) {
                free(result);
                return NULL;
            }
            
            int written = snprintf(temp, temp_size, "%lld", num);
            if (written > 0) {
                if (j + (size_t)written >= out_len) {
                    out_len = j + (size_t)written + len + 1;
                    char* new_result = (char*)realloc(result, out_len);
                    if (new_result == NULL) {
                        free(temp);
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }
                for (int k_idx = 0; k_idx < written; k_idx++) {
                    result[j + k_idx] = temp[k_idx];
                }
                j += written;
            }
            free(temp);
        } else {
            if (j >= out_len - 1) {
                out_len *= 2;
                char* new_result = (char*)realloc(result, out_len);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[j++] = input[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char* str = "The 2 apples cost 15 dollars, and 3 oranges cost 20 dollars.";
    int k = 5;

    char* new_str = increment_numeric_values(str, k);
    if (new_str != NULL) {
        printf("Original: %s\n", str);
        printf("Modified: %s\n", new_str);
        free(new_str);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}