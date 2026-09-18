#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static int count_digits(int n)
{
    int count = 0;
    if (n == 0) {
        return 1;
    }
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

static bool is_armstrong(int n)
{
    if (n < 0) {
        return false;
    }
    
    int original = n;
    int num_digits = count_digits(n);
    long long sum = 0;
    
    while (n != 0) {
        int digit = n % 10;
        long long power = 1;
        
        for (int i = 0; i < num_digits; i++) {
            power *= digit;
            /* Possible weaknesses found:
             * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000000,time:9748,execs:3265,op:havoc,rep:9)
             */
            if (power > LLONG_MAX / digit && i < num_digits - 1) {
                return false;
            }
        }
        
        sum += power;
        if (sum > INT_MAX) {
            return false;
        }
        n /= 10;
    }
    
    return (int)sum == original;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:1848,execs:666,op:havoc,rep:6; likely memory-safety defect
  */

int main(void)
{
    int number;
    int scan_result;
    
    printf("Enter a number: ");
    scan_result = scanf("%d", &number);
    
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * ASan: FPE (AFL crash: id:000001,sig:06,src:000000,time:9748,execs:3265,op:havoc,rep:9)
     */
    if (is_armstrong(number)) {
        printf("%d is an Armstrong number\n", number);
    } else {
        printf("%d is not an Armstrong number\n", number);
    }
    
    return 0;
}