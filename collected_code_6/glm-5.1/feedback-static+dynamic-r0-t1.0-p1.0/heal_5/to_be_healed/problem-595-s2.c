#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
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
    if (len1 != len2) {
        return -1;
    }
    size_t len = len1;
    if (len == 0) {
        return 0;
    }
    
    size_t count_mismatch1 = 0;
    size_t count_mismatch2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count_mismatch1++;
            } else {
                count_mismatch2++;
            }
        }
    }
    
    if (count_mismatch1 != count_mismatch2) {
        return -1;
    }
    return (int)count_mismatch1;
}

int main() {
    const char *s1 = "11001";
    const char *s2 = "00111";
    
    int result = min_swaps(s1, s1);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    result = min_swaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    /* Possible weaknesses found:
     *  Assignment 'result=min_swaps(NULL,s2)', assigned value is -1
     *  Calling function 'min_swaps' returns -1
     */
    result = min_swaps(NULL, s2);
    /* Possible weaknesses found:
     *  Condition 'result==-1' is always true [knownConditionTrueFalse]
     *  Condition 'result==-1' is always true
     */
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}