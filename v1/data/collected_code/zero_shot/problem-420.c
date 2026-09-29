#include <stdio.h>

int cubeSumOfEvenNumbers(int n) {
    int sum = 0;

    for (int i = 2; i <= 2 * n; i += 2) {
        sum += i * i * i;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int result = cubeSumOfEvenNumbers(n);
    printf("Cube sum of first %d even natural numbers: %d\n", n, result);

    return 0;
}