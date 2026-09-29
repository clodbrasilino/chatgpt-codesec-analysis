#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, 101);
    size_t len2 = strnlen(str2, 101);
    
    if (len1 != len2 || len1 == 101 || len2 == 101) {
        return -1;
    }
    
    size_t len = len1;
    
    int count1 = 0, count2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (str1[i] == '1') count1++;
        if (str2[i] == '1') count2++;
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    int mismatch = 0;
    for (size_t i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            mismatch++;
        }
    }
    
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return mismatch / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[102] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[102] = {0};
    
    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    
    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';
    
    size_t actual_len1 = strnlen(str1, 101);
    size_t actual_len2 = strnlen(str2, 101);
    
    if (actual_len1 > 100 || actual_len2 > 100) {
        printf("Not Possible\n");
        return 0;
    }
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}