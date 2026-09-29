#include <stdio.h>
#include <stdlib.h>

long long sum_odd_range(int l, int r) {
    if (l > r) {
        return 0;
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
    
    long long ll = l;
    long long rr = r;
    long long n = (rr - ll) / 2 + 1;
    
    return n * (ll + rr) / 2;
}

int main(void) {
    int l, r;
    
    printf("Enter range (l r): ");
    if (scanf("%d %d", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_odd_range(l, r);
    printf("Sum of odd numbers in range [%d, %d]: %lld\n", l, r, result);
    
    return EXIT_SUCCESS;
}