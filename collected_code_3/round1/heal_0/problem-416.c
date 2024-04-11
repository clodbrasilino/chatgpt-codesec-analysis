#include <stdio.h>

int maxSum(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n == 3) return 2;
    return maxSum(n/2) + maxSum(n/3) + maxSum(n/4);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Maximum sum: %d\n", maxSum(n));
    return 0;
}