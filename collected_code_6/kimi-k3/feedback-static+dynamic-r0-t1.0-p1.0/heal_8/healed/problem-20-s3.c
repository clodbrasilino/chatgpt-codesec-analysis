#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n)
{
    if (n < 7ULL) {
        return false;
    }
    
    for (unsigned long long k = 1ULL; k <= 64ULL; k++) {
        unsigned long long m = 1ULL;
        
        while (1) {
            if (m > (ULLONG_MAX - 1ULL) / k) {
                break;
            }
            
            unsigned long long candidate = m * k + 1ULL;
            
            if (candidate == n) {
                return true;
            }
            
            if (candidate > n) {
                break;
            }
            
            if (m > ULLONG_MAX / 2ULL) {
                break;
            }
            m *= 2ULL;
        }
    }
    
    return false;
}

int main(void)
{
    unsigned long long test_numbers[] = {7ULL, 23ULL, 63ULL, 159ULL, 383ULL, 1ULL, 8ULL, 64ULL};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        if (is_woodall(test_numbers[i])) {
            printf("%llu is a Woodall number\n", test_numbers[i]);
        } else {
            printf("%llu is not a Woodall number\n", test_numbers[i]);
        }
    }
    
    return 0;
}