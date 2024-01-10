#include <stdio.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void capitalizeFirstAndLastLetters(char *str) {
    int i;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    int len = strlen(str);
    
    // capitalize first letter of each word
    for (i = 0; i < len; i++) {
        if (i == 0 || isblank(str[i - 1])) {
            str[i] = toupper(str[i]);
        }
    }
    
    // capitalize last letter of each word
    for (i = 0; i < len; i++) {
        if (isalpha(str[i]) && (i == len - 1 || isblank(str[i + 1]))) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str), stdin);
    
    capitalizeFirstAndLastLetters(str);
    
    printf("Modified string: %s", str);
    
    return 0;
}