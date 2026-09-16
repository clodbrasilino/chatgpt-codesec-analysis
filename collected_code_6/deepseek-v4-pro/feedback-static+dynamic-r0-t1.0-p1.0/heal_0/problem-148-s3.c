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
        
        multiplier *= 10;
    }
    
    return best_part;
}

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