#include <stdio.h>
#include <string.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int min_swaps(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str1);
    int count0 = 0, count1 = 0;
    int swaps = 0;

    for (size_t i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                count0++;
            } else if (str1[i] == '1') {
                count1++;
            }
        }
    }

    if (count0 != count1) return -1;

    char *temp1 = NULL;
    char *temp2 = NULL;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'temp1_len' and 'temp2_len'.
     *  Same expression used in consecutive assignments of 'temp1_len' and 'temp2_len'. [duplicateAssignExpression]
     */
    size_t temp1_len = len + 1;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'temp1_len' and 'temp2_len'.
     */
    size_t temp2_len = len + 1;
    
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    temp1 = (char*)malloc(temp1_len);
    temp2 = (char*)malloc(temp2_len);
    
    if (temp1 == NULL || temp2 == NULL) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(temp1);
        free(temp2);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp1, str1, len);
    temp1[len] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp2, str2, len);
    temp2[len] = '\0';

    while (count0 > 0) {
        int pos0 = -1;
        int pos1 = -1;
        
        for (size_t i = 0; i < len; i++) {
            if (temp1[i] != temp2[i]) {
                if (temp1[i] == '0' && pos0 == -1) {
                    pos0 = (int)i;
                }
                if (temp1[i] == '1' && pos1 == -1) {
                    pos1 = (int)i;
                }
            }
        }

        if (pos0 == -1 || pos1 == -1) {
            break;
        }

        char tmp = temp1[pos0];
        temp1[pos0] = temp1[pos1];
        temp1[pos1] = tmp;
        
        swaps++;
        count0--;
    }

    free(temp1);
    free(temp2);
    
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
        printf("Error reading input\n");
        return 1;
    }
    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", str2) != 1) {
        printf("Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    
    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            printf("First string must contain only 0 and 1\n");
            return 1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            printf("Second string must contain only 0 and 1\n");
            return 1;
        }
    }

    int result = min_swaps(str1, str2);
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}