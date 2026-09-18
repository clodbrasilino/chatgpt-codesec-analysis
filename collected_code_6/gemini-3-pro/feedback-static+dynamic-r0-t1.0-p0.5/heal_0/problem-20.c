#include <stdio.h>
#include <stdbool.h>

bool is_woodall(unsigned long long n) {
    if (n < 1) {
        return false;
    }
    
    unsigned long long w = 0;
    unsigned int i = 1;
    
    while (w < n) {
        w = i * (1ULL << i) - 1;
        if (w == n) {
            return true;
        }
        i++;
    }
    
    return false;
}

int main(void) {
    unsigned long long num;
    
    if (scanf("%llu", &num) != 1) {
        return 1;
    }
    
    if (is_woodall(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}