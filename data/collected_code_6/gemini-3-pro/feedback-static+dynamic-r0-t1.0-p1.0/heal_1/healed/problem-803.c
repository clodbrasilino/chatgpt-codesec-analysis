#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_perfect_square(long long num) {
    if (num < 0) {
        return false;
    }
    unsigned long long root = (unsigned long long)round(sqrt((double)num));
    return (root * root == (unsigned long long)num);
}

int main(void) {
    long long num = 0;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (is_perfect_square(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}