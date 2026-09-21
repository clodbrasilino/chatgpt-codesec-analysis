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
    
    /* Possible weaknesses found:
     *  Assuming condition 'len<(unsigned long)positions' is false
     */
    if (len < (size_t)positions) {
        free(temp);
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, positions);
    temp[positions] = '\0';
    
    /* Possible weaknesses found:
     *  Condition 'len-positions+1>0' is always true [knownConditionTrueFalse]
     */
    if (len - positions + 1 > 0) {
        memmove(str, str + positions, len - positions + 1);
    }
    
    /* Possible weaknesses found:
     *  Condition 'len>=(unsigned long)positions' is always true
     *  Condition 'len>=(unsigned long)positions' is always true [knownConditionTrueFalse]
     */
    if (len >= (size_t)positions) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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