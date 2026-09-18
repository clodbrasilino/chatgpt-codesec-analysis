#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool is_woodall(unsigned long long w) {
    unsigned long long n = 1;
    
    while (n < 64) {
        unsigned long long power_of_two = 1ULL << n;
        
        if (ULLONG_MAX / power_of_two < n) {
            break;
        }
        
        unsigned long long current = n * power_of_two;
        
        if (current - 1 == w) {
            return true;
        }
        
        if (current - 1 > w) {
            return false;
        }
        
        n++;
    }

    return false;
}

int main(void) {
    unsigned long long w;

    if (scanf("%llu", &w) == 1) {
        if (is_woodall(w)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    return 0;
}