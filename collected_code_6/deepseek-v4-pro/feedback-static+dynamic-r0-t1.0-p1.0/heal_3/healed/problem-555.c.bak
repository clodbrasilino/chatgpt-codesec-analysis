#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(long long n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long sum_of_naturals(long long n) {
    return n * (n + 1) / 2;
}

long long difference(long long n) {
    long long sum_n = sum_of_naturals(n);
    long long sum_sq = sum_of_squares(n);
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_sq;
}

int main(void) {
    long long n;
    
    printf("Enter a natural number: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%lld\n", difference(n));
    
    return 0;
}