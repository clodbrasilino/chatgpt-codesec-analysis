#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t len1 = strnlen(str1, 4096);
    size_t len2 = strnlen(str2, 4096);
    
    if (len1 == 0 || len1 != len2 || len1 >= 4096) {
        return 0;
    }
    
    size_t tempSize = 2 * len1 + 1;
    char *temp = (char *)malloc(tempSize);
    if (temp == NULL) {
        return 0;
    }
    
    snprintf(temp, tempSize, "%s%s", str1, str1);
    
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