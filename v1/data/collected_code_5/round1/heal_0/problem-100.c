#include<stdio.h>
#include<string.h>

int isPalindrome(int number) {
    int reversed = 0, remainder, original = number;
    do {
        remainder = number % 10;
        reversed = reversed*10 + remainder;
        number /= 10;
    } while (number != 0);
    return original == reversed;
}

int findNextSmallestPalindrome(int number) {
    while (++number) {
        if(isPalindrome(number)) {
            return number;
        }
    }
}

int main() {
    int number, result;

    printf("Enter a number: ");
    scanf("%d", &number);

    result = findNextSmallestPalindrome(number);

    printf("The next smallest palindrome is: %d", result);

    return 0;
}