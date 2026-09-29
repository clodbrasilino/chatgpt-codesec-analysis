#include <stdio.h>
#include <stdlib.h>

long long sum_even_in_range(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    if (l < 0) {
        l = 0;
    }
    
    if (l % 2 != 0) {
        l++;
    }
    
    if (r % 2 != 0) {
        r--;
    }
    
    if (l > r) {
        return 0;
    }
    
    unsigned long long ul = (unsigned long long)l;
    unsigned long long ur = (unsigned long long)r;
    unsigned long long n = ((ur - ul) / 2ULL) + 1ULL;
    
    unsigned long long total = n * ((ul + ur) / 2ULL);
    return (long long)total;
}

int main(void) {
    long long l;
    long long r;
    long long sum;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    
    sum = sum_even_in_range(l, r);
    printf("%lld\n", sum);
    
    return EXIT_SUCCESS;
}