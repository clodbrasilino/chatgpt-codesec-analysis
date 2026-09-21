#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void leftRotateString(char *str, int positions) {
    if (str == NULL || positions <= 0) {
        return;
    }
    
    size_t len = safe_strlen(str, 1024);
    if (len == 0 || len >= 1024) {
        return;
    }
    
    positions = positions % (int)len;
    if (positions == 0) {
        return;
    }
    
    size_t pos = (size_t)positions;
    /* Possible weaknesses found:
     *  Assuming that condition 'pos>=len' is not redundant
     */
    if (pos >= len) {
        return;
    }
    
    size_t remaining = len - pos;
    
    char *temp = (char *)malloc(pos);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Condition 'pos<=len' is always true
     *  Condition 'pos<=len' is always true [knownConditionTrueFalse]
     */
    if (pos <= len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, pos);
    } else {
        free(temp);
        return;
    }
    
    if (remaining <= len) {
        memmove(str, str + pos, remaining);
    } else {
        free(temp);
        return;
    }
    
    if (pos <= remaining + pos) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + remaining, temp, pos);
    } else {
        free(temp);
        return;
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