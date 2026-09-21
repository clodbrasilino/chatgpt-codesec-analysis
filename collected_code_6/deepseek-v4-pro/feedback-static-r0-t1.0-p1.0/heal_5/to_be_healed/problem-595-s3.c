#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps_to_convert(const char *str1, const char *str2) {
    int len1 = 0;
    int len2 = 0;
    
    while (str1[len1] != '\0') len1++;
    while (str2[len2] != '\0') len2++;
    
    if (len1 != len2) {
        return -1;
    }
    if (len1 == 0) {
        return 0;
    }
    
    int count1_1 = 0, count1_0 = 0;
    int count2_1 = 0, count2_0 = 0;
    
    for (int i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') return -1;
        if (str2[i] != '0' && str2[i] != '1') return -1;
        
        if (str1[i] == '1') count1_1++;
        else count1_0++;
        
        if (str2[i] == '1') count2_1++;
        else count2_0++;
    }
    
    if (count1_1 != count2_1 || count1_0 != count2_0) {
        return -1;
    }
    
    const char *temp_str1 = str1;
    /* Possible weaknesses found:
     *  alloc_size is assigned '(unsigned long)len1+1' here.
     */
    size_t alloc_size = (size_t)len1 + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=(unsigned long)len1' is always false
     *  Condition 'alloc_size<=(unsigned long)len1' is always false [knownConditionTrueFalse]
     */
    if (alloc_size <= (size_t)len1) {
        return -1;
    }
    
    char *temp_str2 = malloc(alloc_size);
    if (temp_str2 == NULL) {
        return -1;
    }
    
    size_t copy_size = (size_t)len1 + 1;
    if (copy_size > alloc_size) {
        free(temp_str2);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp_str2, str2, copy_size);
    temp_str2[len1] = '\0';
    
    int swaps = 0;
    
    for (int i = 0; i < len1; i++) {
        if (temp_str1[i] != temp_str2[i]) {
            int found = 0;
            for (int j = i + 1; j < len1; j++) {
                if (temp_str1[j] != temp_str2[j] && 
                    temp_str1[i] == temp_str2[j] && 
                    temp_str1[j] == temp_str2[i]) {
                    char temp = temp_str2[i];
                    temp_str2[i] = temp_str2[j];
                    temp_str2[j] = temp;
                    swaps++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                for (int j = i + 1; j < len1; j++) {
                    if (temp_str1[j] != temp_str2[j] && 
                        temp_str1[i] != temp_str1[j] && 
                        temp_str2[i] != temp_str2[j]) {
                        char temp = temp_str2[i];
                        temp_str2[i] = temp_str2[j];
                        temp_str2[j] = temp;
                        swaps++;
                        break;
                    }
                }
            }
        }
    }
    
    free(temp_str2);
    return swaps;
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
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%101s", str1) != 1) {
        return 1;
    }
    
    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%101s", str2) != 1) {
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