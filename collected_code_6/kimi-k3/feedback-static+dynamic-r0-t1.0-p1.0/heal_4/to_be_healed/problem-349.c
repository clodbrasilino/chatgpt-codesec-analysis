#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_binary_string(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (is_binary_string(buffer, len)) {
            printf("Binary string\n");
        } else {
            printf("Not a binary string\n");
        }
    }
    
    return 0;
}