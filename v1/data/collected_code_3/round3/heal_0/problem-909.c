#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int num) {
    int reversed = 0;
    int temp = num;

    while (temp != 0) {
        int digit = temp % 10;
        reversed = reversed * 10 + digit;
        temp /= 10;
    }

    return num == reversed;
}

int prevPalindrome(int num) {
    num--;
    while (!isPalindrome(num)) {
        num--;
    }
    return num;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Previous palindrome: %d\n", prevPalindrome(num));
    return 0;
}