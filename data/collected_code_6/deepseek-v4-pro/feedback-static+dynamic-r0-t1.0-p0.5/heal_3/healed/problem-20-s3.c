#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n < 1) return false;
    
    unsigned long long h = 2;
    int k = 1;
    
    while (1) {
        if (h > n / k + 1) break;
        
        unsigned long long woodall = h * k;
        if (woodall == n + 1) return true;
        
        if (h > (unsigned long long)-1 / 2) break;
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