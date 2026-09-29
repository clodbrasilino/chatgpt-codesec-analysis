#include <stdio.h>
#include <stdlib.h>

long long sum_odd_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    long long first_odd = (l % 2 == 0) ? l + 1 : l;
    
    if (first_odd > r) {
        return 0;
    }
    
    long long last_odd = (r % 2 == 0) ? r - 1 : r;
    long long count = (last_odd - first_odd) / 2 + 1;
    
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    long long l, r;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_odd_natural_numbers(l, r));
    
    return EXIT_SUCCESS;
}