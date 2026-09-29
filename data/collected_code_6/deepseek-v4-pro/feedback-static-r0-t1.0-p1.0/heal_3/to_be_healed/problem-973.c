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
    
    /* Possible weaknesses found:
     *  Assuming condition 'len<(unsigned long)positions' is false
     */
    if (len < (size_t)positions) {
        return;
    }
    
    char *temp = (char *)malloc((size_t)positions + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Condition '(unsigned long)positions<=len' is always true
     *  Condition '(unsigned long)positions<=len' is always true [knownConditionTrueFalse]
     */
    if ((size_t)positions <= len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, (size_t)positions);
        temp[positions] = '\0';
    }
    
    size_t remaining = len - (size_t)positions;
    if (remaining > 0) {
        memmove(str, str + (size_t)positions, remaining);
    }
    str[remaining] = '\0';
    
    if ((size_t)positions <= remaining + (size_t)positions) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + remaining, temp, (size_t)positions);
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