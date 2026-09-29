#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

int countSubstrings(const char *str, size_t len) {
    uint64_t count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return (count > INT32_MAX) ? INT32_MAX : (int)count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[4096];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strcspn(str, "\n");
        str[len] = '\0';
        
        int result = countSubstrings(str, len);
        printf("Number of substrings with same first and last characters: %d\n", result);
    } else {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    return 0;
}