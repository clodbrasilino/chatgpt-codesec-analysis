#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSum(int n) {
    if(n <= 1) {
        return n;
    }
    int sum = max((maxSum(n / 2) + maxSum(n / 3) + maxSum(n / 4) + maxSum(n / 5)), n);
    return sum;
}

int main() {
    int n = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Maximum sum: %d\n", maxSum(n));
    return 0;
}