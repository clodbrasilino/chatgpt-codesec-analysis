#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n)
{
    if (n < 7ULL) {
        return false;
    }
    
    for (unsigned long long k = 1ULL; k <= 64ULL; k++) {
        if (k > (ULLONG_MAX - 1ULL) / k) {
            break;
        }
        
        unsigned long long m = 1ULL;
        unsigned long long max_m = (ULLONG_MAX - 1ULL) / k;
        
        while (m <= max_m) {
            unsigned long long product = m * k;
            if (product > ULLONG_MAX - 1ULL) {
                break;
            }
            
            unsigned long long candidate = product + 1ULL;
            
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