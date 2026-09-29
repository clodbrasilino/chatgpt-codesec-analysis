#include <stdio.h>
#include <stdlib.h>

int digit_sum(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

long long find_max_sum_split(long long num) {
    if (num < 0) {
        return -1;
    }
    
    long long best_sum = digit_sum(num);
    long long best_part = 0;
    long long multiplier = 1;
    
    while (multiplier <= num) {
        long long current_part = num % multiplier;
        long long remaining = num - current_part;
        
        if (remaining > 0) {
            int current_sum = digit_sum(current_part) + digit_sum(remaining);
            if (current_sum > best_sum) {
                best_sum = current_sum;
                best_part = current_part;
            }
        }
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1000000000000000000 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000012,time:34796,execs:16912,op:havoc,rep:1)
         */
        multiplier *= 10;
    }
    
    return best_part;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:843,execs:479,op:havoc,rep:7; likely memory-safety defect
  */

int main(void) {
    long long number;
    
    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (number < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }
    
    long long part1 = find_max_sum_split(number);
    long long part2 = number - part1;
    
    printf("Number: %lld\n", number);
    printf("Part 1: %lld\n", part1);
    printf("Part 2: %lld\n", part2);
    printf("Maximum sum of digits: %d\n", digit_sum(part1) + digit_sum(part2));
    
    return 0;
}