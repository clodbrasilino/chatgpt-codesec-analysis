#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    
    if (len1 != len2 || len1 == 0 || len1 > 100) {
        return -1;
    }
    
    int count1_0 = 0, count1_1 = 0;
    int count2_0 = 0, count2_1 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '0') count1_0++;
        else if (s1[i] == '1') count1_1++;
        else return -1;
        
        if (s2[i] == '0') count2_0++;
        else if (s2[i] == '1') count2_1++;
        else return -1;
    }
    
    if (count1_0 != count2_0 || count1_1 != count2_1) {
        return -1;
    }
    
    int mismatch_0_to_1 = 0;
    int mismatch_1_to_0 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' && s2[i] == '1') {
                mismatch_0_to_1++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                mismatch_1_to_0++;
            }
        }
    }
    
    if (mismatch_0_to_1 != mismatch_1_to_0) {
        return -1;
    }
    
    return mismatch_0_to_1;
}

int main() {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t bufsize = 102;
    size_t len1, len2;
    
    str1 = (char *)malloc(bufsize);
    if (str1 == NULL) {
        printf("Not Possible\n");
        return 0;
    }
    
    str2 = (char *)malloc(bufsize);
    if (str2 == NULL) {
        free(str1);
        printf("Not Possible\n");
        return 0;
    }
    
    if (fgets(str1, (int)bufsize, stdin) == NULL) {
        free(str1);
        free(str2);
        printf("Not Possible\n");
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }
    if (len1 > 100 || len1 == 0) {
        printf("Not Possible\n");
        free(str1);
        free(str2);
        return 0;
    }
    
    if (fgets(str2, (int)bufsize, stdin) == NULL) {
        free(str1);
        free(str2);
        printf("Not Possible\n");
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }
    if (len2 > 100 || len2 == 0) {
        printf("Not Possible\n");
        free(str1);
        free(str2);
        return 0;
    }
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    free(str1);
    free(str2);
    
    return 0;
}