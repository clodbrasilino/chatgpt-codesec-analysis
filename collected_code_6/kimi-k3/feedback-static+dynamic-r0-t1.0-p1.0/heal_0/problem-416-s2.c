#include <stdio.h>

int max(int a, int b, int c) {
    int m = (a > b) ? a : b;
    return (m > c) ? m : c;
}

int maxSum(int n) {
    if (n <= 1) {
        return n;
    }
    int result = max(n, maxSum(n / 2) + maxSum(n / 3) + maxSum(n / 4), 0);
    return result;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("Maximum sum: %d\n", maxSum(n));
    return 0;
}