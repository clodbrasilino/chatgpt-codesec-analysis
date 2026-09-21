#include <stdio.h>
#include <string.h>
#include <limits.h>

int find_max_diff(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int max_diff = 0;
    int current_diff = 0;
    size_t len = strnlen(str, 1024);
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '0') {
            current_diff++;
        } else if (str[i] == '1') {
            current_diff--;
        } else {
            return 0;
        }
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }
    
    return max_diff;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        int result = find_max_diff(buffer);
        printf("%d\n", result);
    }
    
    return 0;
}