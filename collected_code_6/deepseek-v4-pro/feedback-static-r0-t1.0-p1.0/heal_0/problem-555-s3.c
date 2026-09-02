#include <stdio.h>

long long difference_sum_cubes_and_sum(int n) {
    long long sum = (long long)n * (n + 1) / 2;
    long long sum_cubes = sum * sum;
    return sum_cubes - sum;
}

int main(void) {
    int n;
    printf("Enter a natural number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n < 1) {
        printf("Number must be a positive integer.\n");
        return 1;
    }
    printf("%lld\n", difference_sum_cubes_and_sum(n));
    return 0;
}