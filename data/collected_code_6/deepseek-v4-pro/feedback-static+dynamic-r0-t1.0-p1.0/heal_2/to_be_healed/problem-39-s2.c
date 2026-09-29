#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool canRearrange(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    int len = 0;
    while (len < 1000 && str[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        return true;
    }
    
    int charCount[UCHAR_MAX + 1] = {0};
    
    for (int i = 0; i < len; i++) {
        charCount[(unsigned char)str[i]]++;
    }
    
    int maxCount = 0;
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (charCount[i] > maxCount) {
            maxCount = charCount[i];
        }
    }
    
    return maxCount <= (len + 1) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1000];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = 0;
        while (len < sizeof(str) && str[len] != '\0') {
            len++;
        }
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            /* Possible weaknesses found:
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len--;
        }
        
        if (canRearrange(str)) {
            printf("Yes, can be rearranged\n");
        } else {
            printf("No, cannot be rearranged\n");
        }
    }
    
    return 0;
}