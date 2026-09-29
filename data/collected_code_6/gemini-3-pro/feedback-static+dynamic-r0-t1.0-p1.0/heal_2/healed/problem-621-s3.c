#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
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
            
            char temp[64];
            int written = snprintf(temp, sizeof(temp), "%lld", num);
            if (written > 0) {
                if (j + (size_t)written >= out_len) {
                    out_len = j + (size_t)written + len + 1;
                    char* new_result = (char*)realloc(result, out_len);
                    if (new_result == NULL) {
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
    char buffer[4096];
    char k_buf[64];
    int k = 0;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(buffer);
    while (len > 0 && (buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
        buffer[len-1] = '\0';
        len--;
    }

    if (fgets(k_buf, sizeof(k_buf), stdin) != NULL) {
        k = atoi(k_buf);
    }

    char* new_str = increment_numeric_values(buffer, k);
    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    }

    return 0;
}