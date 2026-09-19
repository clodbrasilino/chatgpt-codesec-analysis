#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int reversed = 0, original = n, remainder;
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return original == reversed;
}

int previous_palindrome(int n) {
    do {
        n--;
    } while (!is_palindrome(n));
    return n;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }

    int prev_palindrome = previous_palindrome(number);
    printf("The previous palindrome is: %d\n", prev_palindrome);

    return 0;
}