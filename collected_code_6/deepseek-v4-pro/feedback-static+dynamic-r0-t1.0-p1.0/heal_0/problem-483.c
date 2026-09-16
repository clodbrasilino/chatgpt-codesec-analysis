#include <stdio.h>
#include <stdlib.h>

int prime_factors[1000];
int prime_exp[1000];
int prime_count = 0;

void factorize(int x) {
    prime_count = 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            prime_factors[prime_count] = i;
            prime_exp[prime_count] = 0;
            while (x % i == 0) {
                prime_exp[prime_count]++;
                x /= i;
            }
            prime_count++;
        }
    }
    if (x > 1) {
        prime_factors[prime_count] = x;
        prime_exp[prime_count] = 1;
        prime_count++;
    }
}

int factorial_divisible_by_x(int x) {
    if (x <= 0) return -1;
    if (x == 1) return 1;
    
    factorize(x);
    
    int low = 1, high = x, result = x;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int possible = 1;
        
        for (int i = 0; i < prime_count; i++) {
            int count = 0;
            int temp = mid;
            int p = prime_factors[i];
            
            while (temp > 0) {
                temp /= p;
                count += temp;
            }
            
            if (count < prime_exp[i]) {
                possible = 0;
                break;
            }
        }
        
        if (possible) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return result;
}

int main(void) {
    int x;
    printf("Enter a number: ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (x <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return 1;
    }
    
    int result = factorial_divisible_by_x(x);
    printf("%d\n", result);
    
    return 0;
}