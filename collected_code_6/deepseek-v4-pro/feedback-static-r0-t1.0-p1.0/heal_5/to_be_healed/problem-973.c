#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, int positions) {
    if (str == NULL || positions <= 0) {
        return;
    }
    
    size_t len = strnlen(str, 1024);
    if (len == 0 || len == 1024) {
        return;
    }
    
    positions = positions % (int)len;
    if (positions == 0) {
        return;
    }
    
    size_t pos = (size_t)positions;
    char *temp = (char *)malloc(pos);
    if (temp == NULL) {
        return;
    }
    
    if (pos > len) {
        free(temp);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, pos);
    
    if (len - pos > len) {
        free(temp);
        return;
    }
    
    memmove(str, str + pos, len - pos);
    
    if (len - pos + pos > len + pos) {
        free(temp);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - pos, temp, pos);
    
    free(temp);
}

int main(void) {
    char str[] = "HelloWorld";
    int rotateBy = 3;
    
    printf("Original string: %s\n", str);
    leftRotateString(str, rotateBy);
    printf("After left rotation by %d: %s\n", rotateBy, str);
    
    return 0;
}