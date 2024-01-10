#include<stdio.h>

void removeOddCharacters(char *str) {
    int i, j;
  
    // Traverse the string
    /* Possible weaknesses found:
     *  Assuming condition is false
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; str[i] != '\0'; i++) {
        // Check if character at current index is odd
        if (i % 2 == 0) {
            // If odd, copy it to the next even index
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'j++' is initialized [premium-bughuntingUninit]
             *  use of uninitialized value 'j' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            str[j++] = str[i];
        }
    }
  
    // Add null character at the end of new string
    /* Possible weaknesses found:
     *  use of uninitialized value 'j' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
  
    // Input the string
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str), stdin);
  
    // Remove odd characters from the string
    removeOddCharacters(str);
  
    // Output the modified string
    printf("Modified string: %s", str);
  
    return 0;
}