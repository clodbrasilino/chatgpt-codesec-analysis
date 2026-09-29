#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long a, long long b, int n) {
    if (b == 0) {
        return -1;
    }
    if (n <= 0) {
        return -1;
    }
    
    unsigned long long ua = a < 0 ? -(unsigned long long)a : (unsigned long long)a;
    unsigned long long ub = b < 0 ? -(unsigned long long)b : (unsigned long long)b;
    
    if (ub > ULLONG_MAX / 10) {
        return -1;
    }
    
    unsigned long long r = ua % ub;
    int digit = 0;
    
    for (int i = 0; i < n; i++) {
        r *= 10;
        digit = (int)(r / ub);
        r = r % ub;
    }
    
    return digit;
}

int main(void) {
    long long numerator = 22;
    long long denominator = 7;
    int n = 10;
    
    int result = find_nth_digit(numerator, denominator, n);
    if (result != -1) {
        printf("The %dth digit of %lld/%lld is %d\n", n, numerator, denominator, result);
    } else {
        printf("Invalid input or overflow condition detected.\n");
    }
    
    /* Possible weaknesses found:
     *  Assignment 'result=find_nth_digit(1,0,1)', assigned value is -1
     *  Calling function 'find_nth_digit' returns -1
     */
    result = find_nth_digit(1, 0, 1);
    /* Possible weaknesses found:
     *  Condition 'result!=-1' is always false
     *  Condition 'result!=-1' is always false [knownConditionTrueFalse]
     */
    if (result != -1) {
        printf("The %dth digit of %lld/%lld is %d\n", 1, 1LL, 0LL, result);
    } else {
        printf("Invalid input or overflow condition detected.\n");
    }
    
    return 0;
}