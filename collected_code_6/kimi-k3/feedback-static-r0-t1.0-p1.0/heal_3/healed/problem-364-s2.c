#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int min_flips_to_alternate(const char *s, size_t max_len, size_t *result) {
    size_t len;
    size_t flips_start_0 = 0;
    size_t flips_start_1 = 0;
    size_t i;
    
    if (s == NULL || result == NULL) {
        return -1;
    }
    
    len = strnlen(s, max_len);
    
    if (len == max_len && max_len > 0 && s[len - 1] != '\0') {
        return -1;
    }
    
    for (i = 0; i < len; i++) {
        if (s[i] != '0' && s[i] != '1') {
            return -1;
        }
        
        if (i % 2 == 0) {
            if (s[i] != '0') {
                flips_start_0++;
            }
            if (s[i] != '1') {
                flips_start_1++;
            }
        } else {
            if (s[i] != '1') {
                flips_start_0++;
            }
            if (s[i] != '0') {
                flips_start_1++;
            }
        }
    }
    
    *result = (flips_start_0 < flips_start_1) ? flips_start_0 : flips_start_1;
    return 0;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_len;
    size_t result;
    int status;
    
    line_len = getline(&buffer, &buffer_size, stdin);
    if (line_len == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (line_len > 0 && buffer[line_len - 1] == '\n') {
        buffer[line_len - 1] = '\0';
    }
    
    status = min_flips_to_alternate(buffer, buffer_size, &result);
    if (status != 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (printf("%zu\n", result) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}