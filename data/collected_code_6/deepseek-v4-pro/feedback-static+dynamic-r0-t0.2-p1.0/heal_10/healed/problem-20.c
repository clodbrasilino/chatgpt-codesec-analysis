#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0ULL) return false;
    if (n == 1ULL) return true;
    
    unsigned long long m = 1ULL;
    int k = 1;
    
    while (1) {
        if (m > ULLONG_MAX / (unsigned long long)k) return false;
        
        unsigned long long woodall = m * (unsigned long long)k;
        
        if (woodall == 0ULL) return false;
        
        if (woodall - 1ULL == n) return true;
        
        if (woodall - 1ULL > n) return false;
        
        if (m > (ULLONG_MAX - 1ULL) / 2ULL) return false;
        m = m * 2ULL + 1ULL;
        k++;
    }
    
    return false;
}

int main(void) {
    unsigned long long num;
    
    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_woodall(num)) {
        printf("%llu is a Woodall number\n", num);
    } else {
        printf("%llu is not a Woodall number\n", num);
    }
    
    return 0;
}