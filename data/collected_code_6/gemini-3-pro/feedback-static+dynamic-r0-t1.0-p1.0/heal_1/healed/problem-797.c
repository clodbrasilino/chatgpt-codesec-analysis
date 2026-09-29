#include <stdio.h>
#include <stdlib.h>

long long sum_of_odds(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    if (l < 0) {
        l = 0;
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
    
    unsigned __int128 ul = l;
    unsigned __int128 ur = r;
    unsigned __int128 n = ((ur - ul) / 2) + 1;
    unsigned __int128 sum = n * (ul + ur) / 2;
    
    return (long long)(unsigned long long)sum;
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