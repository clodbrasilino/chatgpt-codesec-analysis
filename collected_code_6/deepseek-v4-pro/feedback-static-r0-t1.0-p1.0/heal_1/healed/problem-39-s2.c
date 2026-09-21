#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool canRearrange(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    size_t len = strnlen(str, 1000);
    
    if (len == 0) {
        return true;
    }
    
    int charCount[UCHAR_MAX + 1] = {0};
    
    for (size_t i = 0; i < len; i++) {
        charCount[(unsigned char)str[i]]++;
    }
    
    int maxCount = 0;
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (charCount[i] > maxCount) {
            maxCount = charCount[i];
        }
    }
    
    return maxCount <= (int)(len + 1) / 2;
}

int main(void) {
    char str[1024];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[sizeof(str) - 1] = '\0';
        
        size_t len = strnlen(str, sizeof(str));
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
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