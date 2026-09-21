#include <stdio.h>
#include <string.h>

int flips_required(const char *s, size_t len) {
    if (len == 0) return 0;
    
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

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_string[1024];
    
    if (fgets(binary_string, sizeof(binary_string), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(binary_string, "\n");
    if (len >= sizeof(binary_string)) {
        return 1;
    }
    binary_string[len] = '\0';
    
    if (len == 0) {
        return 1;
    }
    
    size_t valid_len = strspn(binary_string, "01");
    if (valid_len != len) {
        return 1;
    }
    
    int result = flips_required(binary_string, len);
    printf("%d\n", result);
    
    return 0;
}