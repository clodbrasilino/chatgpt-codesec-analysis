#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int lucid_number_leq(int n) {
    if (n <= 0) return -1;
    
    int largest_lucid = -1;
    for (int num = 2; num <= n; num++) {
        int distinct_prime_count = 0;
        int temp = num;
        
        for (int p = 2; p <= temp; p++) {
            if (is_prime(p) && temp % p == 0) {
                distinct_prime_count++;
                while (temp % p == 0) {
                    temp /= p;
                }
            }
        }
        
        if (distinct_prime_count >= 3 && is_prime(distinct_prime_count)) {
            largest_lucid = num;
        }
    }
    
    return largest_lucid;
}

int main(void) {
    int n = 1000;
    int result = lucid_number_leq(n);
    
    if (result != -1) {
        printf("Largest lucid number <= %d: %d\n", n, result);
    } else {
        printf("No lucid number found <= %d\n", n);
    }
    
    return 0;
}