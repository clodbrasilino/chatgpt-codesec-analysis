#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(int n) {
    int reversed = 0, original = n;
    while (n != 0) {
        int remainder = n % 10;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -474796266 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1041,execs:460,op:havoc,rep:2)
         * UBSan: signed integer overflow: 981247512 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1201,execs:523,op:havoc,rep:4)
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