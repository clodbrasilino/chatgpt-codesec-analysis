#include <stdio.h>
#include <limits.h>

unsigned long long sum_of_squares_of_even(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)4 * i * i;
        if (sum > ULLONG_MAX - term) {
            return 0;
        }
        sum += term;
    }

    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    unsigned long long result = sum_of_squares_of_even(n);
    
    if (result == 0 && n > 0) {
        printf("Overflow occurred.\n");
        return 1;
    }
    
    printf("%llu\n", result);
    return 0;
}