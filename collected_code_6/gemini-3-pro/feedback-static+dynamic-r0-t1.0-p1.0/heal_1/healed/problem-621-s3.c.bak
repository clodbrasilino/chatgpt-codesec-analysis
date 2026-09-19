#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t out_cap = len + 128;
    char* result = (char*)malloc(out_cap);
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
            
            char temp[64];
            int written = snprintf(temp, sizeof(temp), "%lld", num);
            if (written > 0) {
                if (j + written + 1 >= out_cap) {
                    out_cap = (j + written) * 2 + 128;
                    char* new_res = (char*)realloc(result, out_cap);
                    if (new_res == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_res;
                }
                memcpy(result + j, temp, written);
                j += written;
            }
        } else {
            if (j + 2 >= out_cap) {
                out_cap = out_cap * 2 + 128;
                char* new_res = (char*)realloc(result, out_cap);
                if (new_res == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_res;
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