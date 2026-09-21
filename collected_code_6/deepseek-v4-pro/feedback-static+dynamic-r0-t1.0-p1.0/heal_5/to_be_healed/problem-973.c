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
    /* Possible weaknesses found:
     *  Assuming condition 'tempSize>len' is false
     */
    if (tempSize > len) {
        return;
    }
    
    char *temp = (char *)malloc(tempSize + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Condition 'tempSize<=len' is always true
     *  Condition 'tempSize<=len' is always true [knownConditionTrueFalse]
     */
    if (tempSize <= len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, tempSize);
    }
    temp[tempSize] = '\0';
    
    memmove(str, str + positions, len - positions);
    
    /* Possible weaknesses found:
     *  First condition
     */
    if ((len - positions) + tempSize <= strSize) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + (len - positions), temp, tempSize);
    }
    
    /* Possible weaknesses found:
     *  The if condition is the same as the previous if condition [duplicateCondition]
     *  Second condition
     */
    if ((len - positions) + tempSize <= strSize) {
        str[len] = '\0';
    }
    
    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024] = "HelloWorld";
    int rotateBy = 3;
    
    printf("Original string: %s\n", str);
    leftRotateString(str, sizeof(str), rotateBy);
    printf("After left rotation by %d: %s\n", rotateBy, str);
    
    return 0;
}