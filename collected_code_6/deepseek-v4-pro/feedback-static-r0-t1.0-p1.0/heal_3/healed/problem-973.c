#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, int positions) {
    if (str == NULL || positions <= 0) {
        return;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }
    
    positions = positions % (int)len;
    if (positions == 0) {
        return;
    }
    
    char *temp = (char *)malloc((size_t)positions);
    if (temp == NULL) {
        return;
    }
    
    memcpy(temp, str, (size_t)positions);
    
    memmove(str, str + positions, len - (size_t)positions);
    
    memcpy(str + len - (size_t)positions, temp, (size_t)positions);
    
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