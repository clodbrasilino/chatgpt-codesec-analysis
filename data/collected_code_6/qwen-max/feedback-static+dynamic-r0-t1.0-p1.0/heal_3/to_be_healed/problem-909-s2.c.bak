#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(long long n) {
    long long reversed = 0, original = n;
    while (n != 0) {
        int remainder = n % 10;
        if (reversed > (LLONG_MAX - remainder) / 10) return false;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return original == reversed;
}

long long previous_palindrome(long long n) {
    do {
        n--;
    } while (!is_palindrome(n));
    return n;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:611,execs:286,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }

    long long prev_palindrome = previous_palindrome(number);
    printf("The previous palindrome is: %lld\n", prev_palindrome);

    return 0;
}