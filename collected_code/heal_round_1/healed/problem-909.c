#include <stdio.h>

int isPalindrome(int num) {
    int reversedNum = 0;
    int originalNum = num;
    
    while (num > 0) {
        reversedNum = reversedNum * 10 + num % 10;
        num /= 10;
    }
    
    return originalNum == reversedNum;
}

int findPreviousPalindrome(int num) {
    while (!isPalindrome(--num));
    return num;
}

int main() {
    int number = 0;
    printf("Enter a number: ");
    scanf("%d", &number);
    
    int previousPalindrome = findPreviousPalindrome(number);
    printf("Previous palindrome: %d\n", previousPalindrome);
    
    return 0;
}