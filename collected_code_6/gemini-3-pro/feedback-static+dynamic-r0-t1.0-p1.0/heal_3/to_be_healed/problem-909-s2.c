#include <stdio.h>

int is_palindrome(long long num) {
    if (num < 0) {
        return 0;
    }
    
    long long original = num;
    long long reversed = 0;
    
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    
    return original == reversed;
}

long long get_previous_palindrome(long long num) {
    if (num <= 0) {
        return -1;
    }
    
    long long current = num - 1;
    
    while (current >= 0) {
        if (is_palindrome(current)) {
            return current;
        }
        current--;
    }
    
    return -1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:12382,execs:1202,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    long long input = 0;
    
    if (scanf("%lld", &input) != 1) {
        return 1;
    }
    
    long long result = get_previous_palindrome(input);
    
    if (result != -1) {
        printf("%lld\n", result);
    } else {
        printf("-1\n");
    }
    
    return 0;
}