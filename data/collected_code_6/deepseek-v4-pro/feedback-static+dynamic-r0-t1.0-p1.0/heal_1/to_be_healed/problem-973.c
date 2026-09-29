#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, int positions) {
    if (str == NULL || positions <= 0) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
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
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, positions);
    temp[positions] = '\0';
    
    memmove(str, str + positions, len - positions + 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + (len - positions), temp, positions);
    
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