#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_even_in_range(unsigned long long l, unsigned long long r) {
    if (l > r) {
        return 0;
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
    
    unsigned long long n = ((r - l) / 2) + 1;
    return n * (l + r) / 2;
}

int main(void) {
    unsigned long long l = 0;
    unsigned long long r = 0;
    
    if (scanf("%llu %llu", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sum_even_in_range(l, r);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}