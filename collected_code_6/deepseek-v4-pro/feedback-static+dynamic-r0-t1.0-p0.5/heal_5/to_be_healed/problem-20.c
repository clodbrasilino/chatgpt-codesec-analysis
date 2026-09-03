#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) return false;
    
    unsigned long long m = 1;
    int k = 1;
    
    while (1) {
        if (k != 0 && m > (n + 1) / k) break;
        
        unsigned long long woodall = k * m - 1;
        if (woodall == n) return true;
        if (woodall > n) break;
        
        k++;
        if (m > ULLONG_MAX / 2) break;
        m *= 2;
    }
    
    return false;
}

int main(void) {
    unsigned long long num;
    
    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_woodall(num)) {
        printf("%llu is a Woodall number\n", num);
    } else {
        printf("%llu is not a Woodall number\n", num);
    }
    
    return 0;
}