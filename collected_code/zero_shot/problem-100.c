#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function to reverse a string
void reverse(char* str, int len) {
    int i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
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
        int digit = num[i] - '0' + carry;
        carry = digit / 10;
        num[i] = digit % 10 + '0';
    }
}

// Function to find next smallest palindrome
void findNextPalindrome(char* num) {
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
    char num[100];
    printf("Enter a number: ");
    scanf("%s", num);
    
    findNextPalindrome(num);
    printf("Next smallest palindrome: %s\n", num);
    
    return 0;
}