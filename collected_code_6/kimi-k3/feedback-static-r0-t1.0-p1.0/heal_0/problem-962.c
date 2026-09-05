#include <stdio.h>
#include <limits.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r || l < 0 || r < 0) {
        return 0;
    }
    
    long long first_even = (l % 2 == 0) ? l : l + 1;
    long long last_even = (r % 2 == 0) ? r : r - 1;
    
    if (first_even > last_even) {
        return 0;
    }
    
    long long count = (last_even - first_even) / 2 + 1;
    
    if (count > 0 && (first_even + last_even) > LLONG_MAX / count) {
        return -1;
    }
    
    return count * (first_even + last_even) / 2;
}

int main(void) {
    long long l, r;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    
    long long result = sum_even_natural_numbers(l, r);
    
    if (result == -1) {
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}