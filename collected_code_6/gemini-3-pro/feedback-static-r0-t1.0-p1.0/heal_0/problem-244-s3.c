#include <stdio.h>
#include <math.h>

long long find_next_perfect_square(long long n) {
    if (n < 0) {
        return 0;
    }
    long long root = (long long)floor(sqrt((double)n));
    long long next_root = root + 1;
    return next_root * next_root;
}

int main(void) {
    long long num;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    long long result = find_next_perfect_square(num);
    printf("%lld\n", result);
    
    return 0;
}