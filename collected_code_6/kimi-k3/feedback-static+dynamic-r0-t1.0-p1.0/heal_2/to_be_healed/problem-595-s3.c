#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int min_swaps(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count0_str1 = 0, count1_str1 = 0;
    int count0_str2 = 0, count1_str2 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '0') {
            count0_str1++;
        } else if (str1[i] == '1') {
            count1_str1++;
        } else {
            return -1;
        }
        
        if (str2[i] == '0') {
            count0_str2++;
        } else if (str2[i] == '1') {
            count1_str2++;
        } else {
            return -1;
        }
    }
    
    if (count0_str1 != count0_str2 || count1_str1 != count1_str2) {
        return -1;
    }
    
    char *temp_str1 = malloc(len1 + 1);
    if (temp_str1 == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp_str1, str1);
    
    int swaps = 0;
    size_t i = 0, j = 0;
    
    while (i < len1 && j < len2) {
        if (temp_str1[i] == str2[j]) {
            i++;
            j++;
        } else {
            size_t k = i + 1;
            while (k < len1 && temp_str1[k] == temp_str1[i]) {
                k++;
            }
            
            if (k < len1) {
                swaps++;
                char temp = temp_str1[i];
                temp_str1[i] = temp_str1[k];
                temp_str1[k] = temp;
            } else {
                free(temp_str1);
                return -1;
            }
        }
    }
    
    free(temp_str1);
    return swaps;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100], str2[100];
    
    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", str1) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99s", str2) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}