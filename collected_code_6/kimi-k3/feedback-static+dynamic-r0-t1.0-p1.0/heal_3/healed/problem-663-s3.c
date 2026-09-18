#include <stdio.h>
#include <limits.h>

long long find_largest_k(long long x, long long y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    
    long long remainder = LLONG_MAX % x;
    long long largest_multiple = LLONG_MAX - remainder;
    
    if (remainder >= y) {
        return largest_multiple + y;
    } else {
        long long diff = x - y;
        if (largest_multiple < LLONG_MIN + diff) {
            return LLONG_MIN;
        }
        return largest_multiple - diff;
    }
}

int main(void) {
    long long x, y;
    
    if (scanf("%lld %lld", &x, &y) != 2) {
        return 1;
    }
    
    long long result = find_largest_k(x, y);
    printf("%lld\n", result);
    
    return 0;
}