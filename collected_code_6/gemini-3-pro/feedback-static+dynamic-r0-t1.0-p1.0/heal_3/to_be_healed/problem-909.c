#include <stdio.h>
#include <stdlib.h>

int is_palindrome(long long num) {
    long long original;
    long long reversed = 0;
    
    if (num < 0) {
        return 0;
    }
    
    original = num;
    
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    
    return original == reversed;
}

long long find_previous_palindrome(long long num) {
    if (num <= 0) {
        return -1;
    }
    
    num--;
    
    while (num >= 0) {
        if (is_palindrome(num)) {
            return num;
        }
        num--;
    }
    
    return -1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:18535,execs:1826,op:havoc,rep:6; likely memory-safety defect
  */

int main(void) {
    long long num;
    long long prev_palindrome;

    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }

    prev_palindrome = find_previous_palindrome(num);

    if (prev_palindrome != -1) {
        printf("%lld\n", prev_palindrome);
    } else {
        printf("-1\n");
    }

    return EXIT_SUCCESS;
}