#include <stdio.h>
#include <math.h>

long long count_odd_factors(long long low, long long high);

long long count_odd_factors(long long low, long long high) {
    if (low > high) {
        return 0;
    }
    if (high < 0) {
        return 0;
    }
    if (low < 0) {
        low = 0;
    }
    
    long long start = (long long)ceil(sqrt((double)low));
    long long end = (long long)floor(sqrt((double)high));
    
    if (start > end) {
        return 0;
    }
    
    return end - start + 1;
}

int main(void) {
    long long low = 1;
    long long high = 100;
    long long count;

    count = count_odd_factors(low, high);
    
    if (printf("%lld\n", count) < 0) {
        return 1;
    }
    
    return 0;
}