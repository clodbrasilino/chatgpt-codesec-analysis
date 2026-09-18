#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

static bool is_armstrong(int number)
{
    if (number < 0) {
        return false;
    }
    
    int original = number;
    int digit_count = 0;
    int temp = number;
    
    if (temp == 0) {
        digit_count = 1;
    } else {
        while (temp != 0) {
            temp /= 10;
            digit_count++;
        }
    }
    
    int sum = 0;
    temp = number;
    
    while (temp != 0) {
        int digit = temp % 10;
        int power = 1;
        
        for (int i = 0; i < digit_count; i++) {
            if (power > INT_MAX / digit) {
                return false;
            }
            power *= digit;
        }
        
        if (sum > INT_MAX - power) {
            return false;
        }
        sum += power;
        temp /= 10;
    }
    
    return sum == original;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:2112,execs:723,op:havoc,rep:6; likely memory-safety defect
  */

int main(void)
{
    int number;
    
    printf("Enter a number: ");
    
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_armstrong(number)) {
        printf("%d is an Armstrong number\n", number);
    } else {
        printf("%d is not an Armstrong number\n", number);
    }
    
    return 0;
}