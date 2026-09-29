#include <stdio.h>
#include <string.h>

int min_swaps_to_convert(const char *str1, const char *str2) {
    int len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }
    
    int len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }
    
    if (len1 != len2) {
        return -1;
    }
    
    int count1_1 = 0, count1_0 = 0;
    int count2_1 = 0, count2_0 = 0;
    int mismatches = 0;
    
    for (int i = 0; i < len1; i++) {
        if (str1[i] == '1') count1_1++;
        else count1_0++;
        
        if (str2[i] == '1') count2_1++;
        else count2_0++;
        
        if (str1[i] != str2[i]) {
            mismatches++;
        }
    }
    
    if (count1_1 != count2_1 || count1_0 != count2_0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[100];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[100];
    for (int i = 0; i < len1; i++) {
        s1[i] = str1[i];
        s2[i] = str2[i];
    }
    s1[len1] = '\0';
    s2[len2] = '\0';
    
    int swaps = 0;
    for (int i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            for (int j = i + 1; j < len1; j++) {
                if (s1[j] != s2[j] && s1[i] == s2[j] && s1[j] == s2[i]) {
                    char temp = s2[i];
                    s2[i] = s2[j];
                    s2[j] = temp;
                    swaps++;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            for (int j = i + 1; j < len1; j++) {
                if (s1[j] != s2[j] && s1[i] != s2[i]) {
                    char temp = s2[i];
                    s2[i] = s2[j];
                    s2[j] = temp;
                    swaps++;
                    break;
                }
            }
        }
    }
    
    return swaps;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[101];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[101];
    
    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", str1) != 1) {
        return 1;
    }
    
    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", str2) != 1) {
        return 1;
    }
    
    int result = min_swaps_to_convert(str1, str2);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}