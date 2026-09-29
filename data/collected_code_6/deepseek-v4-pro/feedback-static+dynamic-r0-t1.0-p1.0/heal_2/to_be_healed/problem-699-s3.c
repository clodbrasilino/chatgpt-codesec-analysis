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
    
    size_t len1 = strnlen(s1, 101);
    size_t len2 = strnlen(s2, 101);
    
    if (len1 != len2 || len1 == 0) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[101], str2[101];
    
    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';
    
    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}