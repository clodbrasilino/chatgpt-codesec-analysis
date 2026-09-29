#include <stdio.h>
#include <string.h>

int flips_required(const char *s) {
    if (s == NULL) return 0;
    
    size_t len = 0;
    while (len < 1001 && s[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len > 1000) return 0;
    
    int flips_start_zero = 0;
    int flips_start_one = 0;
    
    for (size_t i = 0; i < len; i++) {
        char expected_zero_start = (i % 2 == 0) ? '0' : '1';
        char expected_one_start = (i % 2 == 0) ? '1' : '0';
        
        if (s[i] != expected_zero_start) {
            flips_start_zero++;
        }
        if (s[i] != expected_one_start) {
            flips_start_one++;
        }
    }
    
    return flips_start_zero < flips_start_one ? flips_start_zero : flips_start_one;
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) return 0;
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_string[1002];
    
    if (fgets(binary_string, sizeof(binary_string), stdin) == NULL) {
        return 1;
    }
    
    binary_string[sizeof(binary_string) - 1] = '\0';
    
    size_t len = safe_strlen(binary_string, sizeof(binary_string) - 1);
    
    if (len > 0 && binary_string[len - 1] == '\n') {
        binary_string[len - 1] = '\0';
        len--;
    } else {
        int found_newline = 0;
        for (size_t i = 0; i < len; i++) {
            if (binary_string[i] == '\n') {
                binary_string[i] = '\0';
                len = i;
                found_newline = 1;
                break;
            }
        }
        if (!found_newline && len >= sizeof(binary_string) - 2) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            return 1;
        }
    }
    
    if (len == 0 || len > 1000) {
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            return 1;
        }
    }
    
    int result = flips_required(binary_string);
    printf("%d\n", result);
    
    return 0;
}