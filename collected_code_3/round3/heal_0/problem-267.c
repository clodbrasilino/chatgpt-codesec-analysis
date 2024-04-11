#include <stdio.h>

int sumOfSquares(int n) {
    int sum = 0;
    int count = 0;
    int i = 1;

    while (count < n) {
        sum += i * i;
        i += 2;
        count++;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int result = sumOfSquares(n);
    printf("The sum of squares of first %d odd natural numbers is %d\n", n, result);

    return 0;
}