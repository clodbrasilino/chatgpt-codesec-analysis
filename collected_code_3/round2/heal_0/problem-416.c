#include <stdio.h>

int maxSum(int n) {
    if (n < 2)
        return 0;
    if (n == 2)
        return 1;
    if (n == 3)
        return 2;
    if (n == 4)
        return 4;
  
    return maxSum(n - 3) + 3;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Maximum sum: %d\n", maxSum(n));
    return 0;
}