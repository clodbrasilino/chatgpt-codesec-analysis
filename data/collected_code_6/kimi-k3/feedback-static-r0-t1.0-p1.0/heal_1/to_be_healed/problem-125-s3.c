#include <stdio.h>
#include <string.h>
#include <limits.h>

int find_max_diff(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int max_diff = 0;
    int current_diff = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        int result = find_max_diff(buffer);
        printf("%d\n", result);
    }
    
    return 0;
}