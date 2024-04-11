#include <stdio.h>

int sumOfSquares(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += (2*i)*(2*i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of squares of first %d even natural numbers is %d\n", n, sumOfSquares(n));
    return 0;
}