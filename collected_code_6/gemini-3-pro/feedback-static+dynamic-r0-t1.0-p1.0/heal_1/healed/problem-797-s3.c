#include <stdio.h>
#include <stdlib.h>

long long sum_of_odds(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l < 0) {
        l = 1;
    }
    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    
    unsigned long long ul = (unsigned long long)l;
    unsigned long long ur = (unsigned long long)r;
    
    unsigned long long n = (ur - ul) / 2 + 1;
    unsigned long long mid = (ul / 2) + (ur / 2) + 1;
    unsigned long long sum = n * mid;
    
    return (long long)sum;
}

int main(void) {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    long long result = sum_of_odds(l, r);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}