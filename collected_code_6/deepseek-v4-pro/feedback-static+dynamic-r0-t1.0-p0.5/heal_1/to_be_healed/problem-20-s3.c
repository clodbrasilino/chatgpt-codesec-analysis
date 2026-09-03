#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n < 1) return false;
    
    unsigned long long h = 1;
    int k = 1;
    
    while (h <= n) {
        unsigned long long woodall = h * k - 1;
        if (woodall == n) return true;
        if (woodall > n) return false;
        
        if (h > (n + 1) / (k + 1)) break;
        
        h *= 2;
        k++;
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