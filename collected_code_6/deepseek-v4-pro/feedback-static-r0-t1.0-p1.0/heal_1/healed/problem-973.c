#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, int positions) {
    if (str == NULL || positions <= 0) {
        return;
    }
    
    size_t len = strnlen(str, 1024);
    if (len == 0 || len >= 1024) {
        return;
    }
    
    positions = positions % (int)len;
    if (positions == 0) {
        return;
    }
    
    char *temp = (char *)malloc(positions + 1);
    if (temp == NULL) {
        return;
    }
    
    if (len < (size_t)positions) {
        free(temp);
        return;
    }
    
    memcpy(temp, str, positions);
    temp[positions] = '\0';
    
    if (len - positions + 1 > 0) {
        memmove(str, str + positions, len - positions + 1);
    }
    
    if (len >= (size_t)positions) {
        memcpy(str + (len - positions), temp, positions);
    }
    
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