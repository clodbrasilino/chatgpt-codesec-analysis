#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, size_t strSize, int positions) {
    if (str == NULL || positions <= 0 || strSize == 0) {
        return;
    }
    
    size_t len = strnlen(str, strSize);
    if (len == 0 || len >= strSize) {
        return;
    }
    
    positions = positions % (int)len;
    if (positions == 0) {
        return;
    }
    
    size_t tempSize = (size_t)positions;
    if (tempSize > len) {
        return;
    }
    
    char *temp = (char *)malloc(tempSize + 1);
    if (temp == NULL) {
        return;
    }
    
    if (tempSize <= len) {
        memcpy(temp, str, tempSize);
    }
    temp[tempSize] = '\0';
    
    memmove(str, str + positions, len - positions);
    
    if ((len - positions) + tempSize <= strSize) {
        memcpy(str + (len - positions), temp, tempSize);
    }
    
    if ((len - positions) + tempSize <= strSize) {
        str[len] = '\0';
    }
    
    free(temp);
}

int main(void) {
    char str[1024] = "HelloWorld";
    int rotateBy = 3;
    
    printf("Original string: %s\n", str);
    leftRotateString(str, sizeof(str), rotateBy);
    printf("After left rotation by %d: %s\n", rotateBy, str);
    
    return 0;
}