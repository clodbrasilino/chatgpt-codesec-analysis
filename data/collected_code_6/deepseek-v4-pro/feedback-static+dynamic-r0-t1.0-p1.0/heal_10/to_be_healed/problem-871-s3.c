#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t len1 = strnlen(str1, SIZE_MAX);
    size_t len2 = strnlen(str2, SIZE_MAX);
    
    if (len1 == 0 && len2 == 0) {
        return 1;
    }
    
    if (len1 != len2) {
        return 0;
    }
    
    if (len1 > SIZE_MAX / 2 - 1) {
        return 0;
    }
    
    size_t tempSize = 2 * len1 + 1;
    char *temp = (char *)malloc(tempSize);
    if (temp == NULL) {
        return 0;
    }
    
    if (len1 > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str1, len1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp + len1, str1, len1);
    }
    temp[tempSize - 1] = '\0';
    
    int result = (strstr(temp, str2) != NULL);
    
    free(temp);
    return result;
}

int main(void) {
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";
    
    if (areRotations(str1, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    str1 = "ABCD";
    str2 = "ACBD";
    
    if (areRotations(str1, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    str1 = "";
    str2 = "";
    
    if (areRotations(str1, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}