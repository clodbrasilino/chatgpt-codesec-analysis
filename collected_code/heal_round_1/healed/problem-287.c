#include <stdio.h>

int sumOfSquaresOfEvenNumbers(int n) {
    int sum = 0;
    int num = 2;

    for (int i = 0; i < n; i++) {
        sum += (num * num);
        num += 2;
    }

    return sum;
}

int main() {
    int n = 0;
    
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    int result = sumOfSquaresOfEvenNumbers(n);
    printf("Sum of squares of first %d even natural numbers: %d\n", n, result);

    return 0;
}