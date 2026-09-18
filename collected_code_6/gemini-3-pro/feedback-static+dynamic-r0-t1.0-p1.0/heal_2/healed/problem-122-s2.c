#include <stdio.h>
#include <stdlib.h>

int is_smart_number(long long num) {
    int prime_count = 0;
    
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            prime_count++;
            while (num % i == 0) {
                num /= i;
            }
        }
    }
    
    if (num > 1) {
        prime_count++;
    }
    
    return (prime_count >= 3);
}

long long find_nth_smart_number(int n) {
    if (n <= 0) {
        return -1;
    }
    
    int count = 0;
    long long current = 1;

    while (count < n) {
        current++;
        if (is_smart_number(current)) {
            count++;
        }
    }
    
    return current;
}

int main(void) {
    int n;
    
    while (scanf("%d", &n) == 1) {
        if (n <= 0) {
            continue;
        }

        long long result = find_nth_smart_number(n);
        
        if (result != -1) {
            printf("%lld\n", result);
        }
    }
    
    return 0;
}