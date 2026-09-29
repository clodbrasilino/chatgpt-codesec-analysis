#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_of_digits(long long n) {
    int sum = 0;
    unsigned long long un;
    if (n < 0) {
        un = (unsigned long long)(-(n + 1)) + 1;
    } else {
        un = (unsigned long long)n;
    }
    while (un > 0) {
        sum += (int)(un % 10);
        un /= 10;
    }
    return sum;
}

void maximize_digit_sum_split(long long num, long long *part1, long long *part2, int *max_sum) {
    if (part1 == NULL || part2 == NULL || max_sum == NULL) {
        return;
    }
    
    unsigned long long unum;
    if (num < 0) {
        unum = (unsigned long long)(-(num + 1)) + 1;
    } else {
        unum = (unsigned long long)num;
    }
    
    *max_sum = -1;
    *part1 = 0;
    *part2 = num;
    
    unsigned long long divisor = 1;
    
    while (divisor <= unum) {
        unsigned long long left = unum / divisor;
        unsigned long long right = unum % divisor;
        
        int current_sum = sum_of_digits((long long)left) + sum_of_digits((long long)right);
        
        if (current_sum > *max_sum) {
            *max_sum = current_sum;
            *part1 = (long long)left;
            *part2 = (long long)right;
        }
        
        if (divisor > ULLONG_MAX / 10) {
            break;
        }
        divisor *= 10;
    }
}

int main(void) {
    long long number;
    long long part1, part2;
    int max_sum;
    
    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    maximize_digit_sum_split(number, &part1, &part2, &max_sum);
    
    printf("First part: %lld\n", part1);
    printf("Second part: %lld\n", part2);
    printf("Sum of digits: %d\n", max_sum);
    
    return EXIT_SUCCESS;
}