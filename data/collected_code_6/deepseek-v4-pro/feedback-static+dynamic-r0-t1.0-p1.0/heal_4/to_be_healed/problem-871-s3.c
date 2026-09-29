#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    
    if (len1 == 0 && len2 == 0) {
        return 1;
    }
    
    if (len1 != len2) {
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