#include <stdio.h>
#include <stdbool.h>

bool is_palindrome(long num) {
    long original_num = num, reversed_num = 0;
    while (num > 0) {
        reversed_num = reversed_num * 10 + num % 10;
        num /= 10;
    }
    return original_num == reversed_num;
}

long previous_palindrome(long n) {
    long prev = n - 1;
    while (prev > 0 && !is_palindrome(prev)) {
        prev--;
    }
    return prev;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:7313,execs:263,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter a number: ");
    scanf("%ld", &n);
    long prev_palindrome = previous_palindrome(n);
    if (prev_palindrome > 0) {
        printf("Previous palindrome: %ld\n", prev_palindrome);
    } else {
        printf("No previous palindrome found.\n");
    }
    return 0;
}