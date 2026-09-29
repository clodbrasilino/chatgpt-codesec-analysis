#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'remainder' can be reduced. [variableScope]
     */
    int reversed = 0, original = n, remainder;
    while (n != 0) {
        remainder = n % 10;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 996008731 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1079,execs:508,op:havoc,rep:5)
         * UBSan: signed integer overflow: -626816684 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:517,execs:257,op:havoc,rep:1)
         */
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