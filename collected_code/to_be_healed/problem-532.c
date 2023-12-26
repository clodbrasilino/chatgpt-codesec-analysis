#include <stdio.h>
#include <string.h>

// Function to check if the two given strings are permutations of each other
int arePermutations(char* str1, char* str2) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int len2 = strlen(str2);
    
    // If the lengths are not equal, they cannot be permutations
    if (len1 != len2) {
        return 0;
    }
    
    // Create a character count array to store the count of each character
    int count[256] = {0};
    
    // Increment the count array for characters in str1
    for (int i = 0; i < len1; i++) {
        count[str1[i]]++;
    }
    
    // Decrement the count array for characters in str2
    for (int i = 0; i < len2; i++) {
        /* Possible weaknesses found:
         *  read of 1 byte from after the end of 'str2'
         *  valid subscripts for 'str2' are '[0]' to '[4]'
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         */
        count[str2[i]]--;
    }
    
    // If any count value in the array is non-zero, they are not permutations
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }
    
    // If all count values are zero, they are permutations
    return 1;
}

int main() {
    char str1[] = "abcd";
    char str2[] = "dcba";
    
    if (arePermutations(str1, str2)) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }
    
    return 0;
}