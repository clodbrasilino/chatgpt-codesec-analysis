#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t len1 = strnlen(str1, 4096);
    size_t len2 = strnlen(str2, 4096);
    
    if (len1 != len2 || len1 == 0) {
        return 0;
    }
    
    if (len1 > 2048) {
        return 0;
    }
    
    size_t total_size = 2 * len1 + 1;
    char *temp = (char *)malloc(total_size);
    if (temp == NULL) {
        return 0;
    }
    
    if (len1 > 0) {
        /* Possible weaknesses found:
         *  Assuming condition 'len1>total_size-len1' is false
         */
        if (len1 > total_size - len1) {
            free(temp);
            return 0;
        }
        
        if (len1 <= total_size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp, str1, len1);
        } else {
            free(temp);
            return 0;
        }
        
        /* Possible weaknesses found:
         *  Condition 'len1<=total_size-len1' is always true [knownConditionTrueFalse]
         *  Condition 'len1<=total_size-len1' is always true
         */
        if (len1 <= total_size - len1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp + len1, str1, len1);
        } else {
            free(temp);
            return 0;
        }
    }
    temp[total_size - 1] = '\0';
    
    int result = (strstr(temp, str2) != NULL);
    
    free(temp);
    return result;
}

int main(void) {
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";
    
    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }
    
    return 0;
}