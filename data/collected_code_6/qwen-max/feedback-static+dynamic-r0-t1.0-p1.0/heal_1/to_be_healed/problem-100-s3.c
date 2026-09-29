#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int reverse(int n, int digits) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    if (digits % 2 == 0) {
        rev /= 10;
    }
    return rev;
}

bool isPalindrome(int n) {
    int original = n, reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return original == reversed;
}

int getNextSmallestPalindrome(int n) {
    if (n < 0) return -1;
    int next = n + 1;
    while (!isPalindrome(next)) {
        next++;
    }
    return next;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:682,execs:266,op:havoc,rep:7; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = getNextSmallestPalindrome(n);
    printf("Next smallest palindrome: %d\n", result);
    return 0;
}