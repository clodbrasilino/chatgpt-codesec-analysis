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
    
    long long n = ((r - l) / 2) + 1;
    return n * (l + r) / 2;
}

int main(void) {
    long long l;
    long long r;
    long long sum;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    sum = sum_even_in_range(l, r);
    printf("%lld\n", sum);
    
    return EXIT_SUCCESS;
}