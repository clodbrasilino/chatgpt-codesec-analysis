#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>

bool is_abundant(int n) {
    if (n <= 1) {
        return false;
    }
    
    int64_t sum = 1;
    int sqrt_n = (int)sqrt((double)n);
    
    for (int i = 2; i <= sqrt_n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                int64_t complement = n / i;
                if (sum > INT64_MAX - complement) {
                    return true;
                }
                sum += complement;
            }
        }
        if (sum > (int64_t)n) {
            return true;
        }
    }
    
    return sum > (int64_t)n;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (num < 0) {
        fprintf(stderr, "Negative numbers are not supported\n");
        return 1;
    }
    
    if (is_abundant(num)) {
        printf("%d is an abundant number\n", num);
    } else {
        printf("%d is not an abundant number\n", num);
    }
    
    return 0;
}