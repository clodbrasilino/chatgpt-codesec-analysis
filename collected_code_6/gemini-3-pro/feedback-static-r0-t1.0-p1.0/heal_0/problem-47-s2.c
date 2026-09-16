#include <stdio.h>
#include <stdlib.h>

int find_last_digit(long long a, long long b) {
    if (a < 0 || b < 0 || a > b) {
        return -1;
    }
    
    if (a == b) {
        return 1;
    }
    
    if ((b - a) >= 5) {
        return 0;
    }
    
    long long result = 1;
    for (long long i = a + 1; i <= b; i++) {
        result = (result * (i % 10)) % 10;
    }
    
    return (int)result;
}

int main() {
    long long a, b;
    
    if (scanf("%lld %lld", &a, &b) != 2) {
        return EXIT_FAILURE;
    }
    
    int last_digit = find_last_digit(a, b);
    
    if (last_digit == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%d\n", last_digit);
    
    return EXIT_SUCCESS;
}