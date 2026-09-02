#include <stdio.h>

long long centered_hexagonal(int n) {
    if (n <= 0) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

int main(void) {
    int n = 10;
    long long result = centered_hexagonal(n);
    
    if (n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}