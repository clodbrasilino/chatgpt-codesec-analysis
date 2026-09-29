#include <stdio.h>
#include <string.h>

int min_swaps_to_convert(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len2 = strlen(str2);
    
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
    
    int swaps = 0;
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            for (int j = i + 1; j < len1; j++) {
                if (str1[j] != str2[j] && str1[i] == str2[j] && str1[j] == str2[i]) {
                    char temp = str2[i];
                    /* Possible weaknesses found:
                     *  read-only variable is not assignable
                     *  assignment of read-only location '*(str2 + (sizetype)i)'
                     */
                    str2[i] = str2[j];
                    /* Possible weaknesses found:
                     *  assignment of read-only location '*(str2 + (sizetype)j)'
                     *  read-only variable is not assignable
                     */
                    str2[j] = temp;
                    swaps++;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            for (int j = i + 1; j < len1; j++) {
                /* Possible weaknesses found:
                 *  Same expression 'str1[j]!=str2[j]' found multiple times in chain of '&&' operators because 'str1[j]!=str2[j]' and 'str2[j]!=str1[j]' represent the same value. [knownConditionTrueFalse]
                 *  Condition 'str2[j]!=str1[j]' is always true [knownConditionTrueFalse]
                 */
                if (str1[j] != str2[j] && str1[i] != str2[i] && str2[j] != str1[j]) {
                    char temp = str2[i];
                    /* Possible weaknesses found:
                     *  read-only variable is not assignable
                     *  assignment of read-only location '*(str2 + (sizetype)i)'
                     */
                    str2[i] = str2[j];
                    /* Possible weaknesses found:
                     *  assignment of read-only location '*(str2 + (sizetype)j)'
                     *  read-only variable is not assignable
                     */
                    str2[j] = temp;
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
    char str1[100], str2[100];
    
    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", str1) != 1) {
        return 1;
    }
    
    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", str2) != 1) {
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