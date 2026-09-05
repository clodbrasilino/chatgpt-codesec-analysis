#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n)
{
    if (n < 1ULL) {
        return false;
    }
    
    for (unsigned long long k = 1ULL; k < 64ULL; k++) {
        unsigned long long woodall;
        
        if (k == 1ULL) {
            woodall = 1ULL;
        } else {
            if (k > (ULLONG_MAX - 1ULL) / k) {
                break;
            }
            
            unsigned long long k_squared = k * k;
            
            if (k_squared > ULLONG_MAX - 1ULL) {
                break;
            }
            
            woodall = k_squared + 1ULL;
        }
        
        if (woodall == n) {
            return true;
        }
        
        if (woodall > n) {
            break;
        }
    }
    
    return false;
}

int main(void)
{
    unsigned long long test_numbers[] = {1ULL, 7ULL, 23ULL, 63ULL, 159ULL, 383ULL, 8ULL, 64ULL};
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