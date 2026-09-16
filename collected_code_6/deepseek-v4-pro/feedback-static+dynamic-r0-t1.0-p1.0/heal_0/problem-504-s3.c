#include <stdio.h>

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long cube = (long long)i * i * i;
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a natural number: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    printf("Cube sum = %lld\n", cube_sum(n));
    return 0;
}