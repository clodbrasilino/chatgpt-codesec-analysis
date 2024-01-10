#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function to reverse a string
void reverse(char* str, int len) {
    int i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        char temp = str[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'str[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to increment the middle characters
void incrementMid(char* num, int len) {
    int mid = len / 2;
    int carry = 1;
    int i;
    for (i = mid - 1; i >= 0; i--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'num[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int digit = num[i] - '0' + carry;
        carry = digit / 10;
        num[i] = digit % 10 + '0';
    }
}

// Function to find next smallest palindrome
void findNextPalindrome(char* num) {
    /* Possible weaknesses found:
     *  Cannot determine that 'num[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(num);
    int mid = len / 2;
    
    // Check if number is already palindrome
    int i;
    for (i = 0; i < mid; i++) {
        if (num[i] != num[len - 1 - i]) {
            break;
        }
    }
    
    // If not palindrome, increment the middle characters
    if (i != mid || len % 2 == 1) {
        incrementMid(num, len);
    }
    
    // Make right side same as left side
    for (i = mid; i < len; i++) {
        num[i] = num[len - 1 - i];
    }
}

// Test the function
int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char num[100];
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", num);
    
    findNextPalindrome(num);
    printf("Next smallest palindrome: %s\n", num);
    
    return 0;
}