#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int min_swaps_to_convert(char *str1, char *str2) {
    int len1 = strlen(str1);
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
    
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *temp_str2 = malloc(len1 + 1);
    if (temp_str2 == NULL) {
        return -1;
    }
    strcpy(temp_str2, str2);
    
    int swaps = 0;
    for (int i = 0; i < len1; i++) {
        if (str1[i] != temp_str2[i]) {
            for (int j = i + 1; j < len1; j++) {
                if (str1[j] != temp_str2[j] && str1[i] == temp_str2[j] && str1[j] == temp_str2[i]) {
                    char temp = temp_str2[i];
                    temp_str2[i] = temp_str2[j];
                    temp_str2[j] = temp;
                    swaps++;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < len1; i++) {
        if (str1[i] != temp_str2[i]) {
            for (int j = i + 1; j < len1; j++) {
                if (str1[j] != temp_str2[j]) {
                    char temp = temp_str2[i];
                    temp_str2[i] = temp_str2[j];
                    temp_str2[j] = temp;
                    swaps++;
                    break;
                }
            }
        }
    }
    
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     */
    free(temp_str2);
    return swaps;
}

int main(void) {
    char str1[100], str2[100];
    
    printf("Enter first binary string: ");
    if (scanf("%99s", str1) != 1) {
        return 1;
    }
    
    printf("Enter second binary string: ");
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