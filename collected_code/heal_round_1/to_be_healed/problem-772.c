#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isalnum'
  */

void removeWordsWithKLength(char* str, int k) {
    int i, j, wordStart, wordEnd, len;
    // Initialize wordStart with -1
    wordStart = -1;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    len = strlen(str);
    
    // Iterate through the string
    for (i = 0; i <= len; i++) {
        // If current character is letter or digit
        /* Possible weaknesses found:
         *  implicit declaration of function 'isalnum' [-Wimplicit-function-declaration]
         */
        if (isalnum(str[i])) {
            // If wordStart is -1, set it to the current index
            if (wordStart == -1) {
                wordStart = i;
            }
        } 
        else {
            // If wordStart is not -1, then a word is found
            if (wordStart != -1) {
                wordEnd = i - 1;
                int wordLen = wordEnd - wordStart + 1;
                
                // If word length is not equal to k, print the word
                if (wordLen != k) {
                    for (j = wordStart; j <= wordEnd; j++) {
                        printf("%c", str[j]);
                    }
                    printf(" ");
                }
                wordStart = -1;
            }
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    int k;
    
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str), stdin);
    printf("Enter the length of words to remove: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'k' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &k);
    
    removeWordsWithKLength(str, k);
    
    return 0;
}