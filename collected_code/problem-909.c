#include <stdio.h>

int isPalindrome(int num) {
    int reversedNum = 0;
    int originalNum = num;
    
    while (num > 0) {
        reversedNum = reversedNum * 10 + num % 10;
        num /= 10;
    }
    
    if (originalNum == reversedNum) {
        return 1;
    } else {
        return 0;
    }
}

int findPreviousPalindrome(int num) {
    num--;
    
    while (1) {
        if (isPalindrome(num)) {
            return num;
        }
        num--;
    }
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    
    int previousPalindrome = findPreviousPalindrome(number);
    printf("Previous palindrome: %d\n", previousPalindrome);
    
    return 0;
}